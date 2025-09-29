#include "kalmanfilter.h"

QString KalmanFilter::name() { return "KalmanFilter"; }

KalmanFilter::KalmanFilter() {
    _has1stPosition = _has2ndPosition = false;

    // Initialize state matrices
    Px = Matrix::diag(3, KalmanFilter::_p);
    Py = Matrix::diag(3, KalmanFilter::_p);

    // Initialize model matrices
    A = Matrix::identity(3);

    H.setSize(1, 3);
    H.set(0, 0, 1);

    Q.setSize(3, 3);

    R.setSize(1, 1);
    R.set(0, 0, pow(KalmanFilter::_r, 2));

    _timer.start();
}

void KalmanFilter::updateMatrices(const float T) {
    // Update A with time (T)
    A.set(0, 1, T);
    A.set(0, 2, pow(T, 2) / 2);
    A.set(1, 2, T);

    /// Time update / PREDICT
    // Project state ahead
    X.matrix() = A * X.matrix();
    Y.matrix() = A * Y.matrix();

    // Update Q with time (T)
    Q.set(0, 0, pow(T, 4) / 4);
    Q.set(0, 1, pow(T, 3) / 2);
    Q.set(0, 2, pow(T, 2) / 2);
    Q.set(1, 0, pow(T, 3) / 2);
    Q.set(1, 1, pow(T, 2));
    Q.set(1, 2, T);
    Q.set(2, 0, pow(T, 2) / 2);
    Q.set(2, 1, T);
    Q.set(2, 2, 1);
    Q *= pow(KalmanFilter::_sigma_a, 2);

    // Project the error covariance ahead
    Px = A * Px * A.transposed() + Q;
    Py = A * Py * A.transposed() + Q;
}

void KalmanFilter::iterate(const Position &pos) {

    // Check if position is known
    if (pos.isInvalid())
        return this->predict();

    // Get iteration time
    _timer.stop();
    const float T = _timer.getSeconds();
    _timer.start();

    // Initial states
    if (_has1stPosition == false) {
        X.setPosition(pos.x());
        Y.setPosition(pos.y());
        _has1stPosition = true;
        return;
    }
    if (_has2ndPosition == false) {
        X.setVelocity((pos.x() - X.getPosition()) / T);
        X.setPosition(pos.x());
        Y.setVelocity((pos.y() - Y.getPosition()) / T);
        Y.setPosition(pos.y());
        _has2ndPosition = true;
        return;
    }

    updateMatrices(T);

    /// Measurement update / CORRECT
    // Compute the Kalman gain
    Matrix Kx = Px * H.transposed() * (1 / (H * Px * H.transposed() + R).get(0, 0));
    Matrix Ky = Py * H.transposed() * (1 / (H * Py * H.transposed() + R).get(0, 0));

    // Update estimate with measurement Zk
    X.matrix() = X.matrix() + Kx * (pos.x() - (H * X.matrix()).get(0, 0));
    Y.matrix() = Y.matrix() + Ky * (pos.y() - (H * Y.matrix()).get(0, 0));

    // Update the error covariance
    const Matrix I = Matrix::identity(3);
    Px = (I - Kx * H) * Px;
    Py = (I - Ky * H) * Py;
}

void KalmanFilter::predict() {

    // Get iteration time
    _timer.stop();
    const float T = _timer.getSeconds();
    _timer.start();

    // Check initial states, if do not have, quit. cannot make prevision...
    if (_has1stPosition == false || _has2ndPosition == false) {
        return;
    }

    updateMatrices(T);
}

Position KalmanFilter::getPosition() const { return {true, X.getPosition(), Y.getPosition()}; }

Velocity KalmanFilter::getVelocity() const { return {true, X.getVelocity(), Y.getVelocity()}; }

Velocity KalmanFilter::getAcceleration() const {
    return {true, X.getAcceleration(), Y.getAcceleration()};
}

void KalmanFilter::setEnabled(bool enable) { enabled = enable; }

bool KalmanFilter::getEnabled() { return enabled; }
