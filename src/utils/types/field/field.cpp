#include "field.h"
#include <src/utils/types/field/field_default_3v3.h>
#include <src/utils/types/field/field_default_5v5.h>

Field::Field(bool is5v5) {
    if (!is5v5) {
        _fieldLength = Field_Default_3v3::kFieldLength;
        _fieldWidth = Field_Default_3v3::kFieldWidth;
        _goalWidth = Field_Default_3v3::kGoalWidth;
        _goalDepth = Field_Default_3v3::kGoalDepth;
        _centerRadius = Field_Default_3v3::kCenterRadius;
        _defenseRadius = Field_Default_3v3::kDefenseRadius;
        _defenseStretch = Field_Default_3v3::kDefenseStretch;
        _bigDefenseRadius = -1;
        _bigDefenseStretch = -1;
        _boundaryWidth = Field_Default_3v3::kBoundaryWidth;
        _kFieldFBMarkX = Field_Default_3v3::kFieldFBMarkX;
        _kFieldFBMarkY = Field_Default_3v3::kFieldFBMarkY;
        _kRobotFBDistance = Field_Default_3v3::kRobotFBDistance;

        for (const auto &kLeftGoalLine : Field_Default_3v3::kLeftGoalLines) {
            _leftGoalLines.push_back(kLeftGoalLine);
        }

        for (const auto &kRightGoalLine : Field_Default_3v3::kRightGoalLines) {
            _rightGoalLines.push_back(kRightGoalLine);
        }

        for (const auto &kFieldLine : Field_Default_3v3::kFieldLines) {
            _fieldLines.push_back(kFieldLine);
        }

        for (const auto &kFieldArc : Field_Default_3v3::kFieldArcs) {
            _fieldArcs.push_back(kFieldArc);
        }

        for (const auto &kFieldTriangle : Field_Default_3v3::kFieldTriangles) {
            _fieldTriangles.push_back(kFieldTriangle);
        }
    } else {
        _fieldLength = Field_Default_5v5::kFieldLength;
        _fieldWidth = Field_Default_5v5::kFieldWidth;
        _goalWidth = Field_Default_5v5::kGoalWidth;
        _goalDepth = Field_Default_5v5::kGoalDepth;
        _centerRadius = Field_Default_5v5::kCenterRadius;
        _defenseRadius = Field_Default_5v5::kDefenseRadius;
        _defenseStretch = Field_Default_5v5::kDefenseStretch;
        _bigDefenseRadius = Field_Default_5v5::kBigDefenseRadius;
        _bigDefenseStretch = Field_Default_5v5::kBigDefenseStretch;
        _boundaryWidth = Field_Default_5v5::kBoundaryWidth;
        _kFieldFBMarkX = Field_Default_5v5::kFieldFBMarkX;
        _kFieldFBMarkY = Field_Default_5v5::kFieldFBMarkY;
        _kRobotFBDistance = Field_Default_5v5::kRobotFBDistance;

        for (const auto &kLeftGoalLine : Field_Default_5v5::kLeftGoalLines) {
            _leftGoalLines.push_back(kLeftGoalLine);
        }

        for (const auto &kRightGoalLine : Field_Default_5v5::kRightGoalLines) {
            _rightGoalLines.push_back(kRightGoalLine);
        }

        for (const auto &kFieldLine : Field_Default_5v5::kFieldLines) {
            _fieldLines.push_back(kFieldLine);
        }

        for (const auto &kFieldArc : Field_Default_5v5::kFieldArcs) {
            _fieldArcs.push_back(kFieldArc);
        }

        for (const auto &kFieldTriangle : Field_Default_5v5::kFieldTriangles) {
            _fieldTriangles.push_back(kFieldTriangle);
        }
    }
}

FieldLine::FieldLine() = default;

FieldLine::FieldLine(const FieldLine &other) = default;

FieldLine::FieldLine(const std::string &marking_name, double p1_x_, double p1_y_, double p2_x_,
                     double p2_y_, double thickness_)
    : p1_x(p1_x_), p1_y(p1_y_), p2_x(p2_x_), p2_y(p2_y_), thickness(thickness_) {
    name.fromStdString(marking_name);
}

FieldCircularArc::FieldCircularArc() = default;

FieldCircularArc::FieldCircularArc(const FieldCircularArc &other) = default;

FieldCircularArc::FieldCircularArc(const std::string &marking_name, double center_x_,
                                   double center_y_, double radius_, double a1_, double a2_,
                                   double thickness_)
    : center_x(center_x_), a1(a1_), a2(a2_), center_y(center_y_), radius(radius_),
      thickness(thickness_) {
    name.fromStdString(marking_name);
}

FieldTriangle::FieldTriangle() = default;

FieldTriangle::FieldTriangle(const FieldTriangle &other) = default;

FieldTriangle::FieldTriangle(const std::string &marking_name, double p1_x_, double p1_y_,
                             double p2_x_, double p2_y_, double p3_x_, double p3_y_,
                             double thickness_)
    : p1_x(p1_x_), p1_y(p1_y_), p2_x(p2_x_), p2_y(p2_y_), p3_x(p3_x_), p3_y(p3_y_),
      thickness(thickness_) {
    name.fromStdString(marking_name);
}
