#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QMutex>

#include <include/packet.pb.h>
#include <include/vssref_common.pb.h>
#include <src/soccerview/fieldview/gltext/gltext.h>
#include <src/utils/timer/timer.h>
#include <src/utils/types/field/field.h>
#include <src/world/entities/vision/vision.h>

class FieldView : public QGLWidget {
    Q_OBJECT
  public:
    FieldView(QWidget *parent = nullptr);
    void setField(Field *fieldPointer);
    void setVisionModule(Vision *visionPointer);
    void setConstants(Constants *constantsPointer);
    void setStuckedTime(float time);

  protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    QSize sizeHint() const override { return {PreferedWidth, PreferedHeight}; }

  private:
    // GL Constants
    static constexpr double minZValue = -10;
    static constexpr double maxZValue = 10;
    static constexpr double FieldZ = 1.0;
    static constexpr double BallZ = 2.0;
    static constexpr double RobotZ = 3.0;
    static const int PreferedWidth = 750;  // widgetWidth * 1.23
    static const int PreferedHeight = 516; // widgetHeight * 1.23
    static constexpr double MinRedrawInterval =
        0.01; /// Minimum time between graphics updates (limits the fps)

    // Mouse events
    double viewScale{};
    double viewXOffset{};
    double viewYOffset{};
    int mouseStartX{};
    int mouseStartY{};

    // Vision
    Vision *vision{};
    Vision *getVision();

    // Field
    Field *field{};
    Field *getField();

    // Constants
    Constants *constants{};
    Constants *getConstants();

    // Stucked ball timer text
    float _stuckedBallTime{0.0f};

    // Util functions
    void recomputeProjection();
    void drawFieldLines();
    void drawStuckedTime();
    void drawFieldLine(const FieldLine &fieldLine);
    void drawQuad(QVector2D point1, QVector2D point2, double z);
    void drawQuad(QVector2D vert1, QVector2D vert2, QVector2D vert3, QVector2D vert4, double z);
    void drawArc(QVector2D loc, double r1, double r2, double theta1, double theta2, double z = 0.0,
                 double dTheta = -1);
    void drawTriangle(QVector2D v1, QVector2D v2, QVector2D v3, double z);
    void drawRobot(VSSRef::Color teamColor, quint8 robotId, QVector2D robotPosition,
                   double robotOrientation);
    void drawText(QVector2D position, double angle, double size, QString text);
    void drawFieldObjects();

    // Graphics mutex
    QMutex graphicsMutex;

    // GLText
    GLText glText;

    // Timer
    Timer timer;

  signals:
    void postRedraw();

  public slots:
    void resetView();
    void updateField();

  private slots:
    void redraw();
};

#endif // FIELDVIEW_H
