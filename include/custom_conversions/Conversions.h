//
// Created by nearlab on 14/12/16.
//

#ifndef TELEOP_VISION_CONVERSIONS_HPP_HPP
#define TELEOP_VISION_CONVERSIONS_HPP_HPP

#include <vector>
#include <geometry_msgs/Pose.h>
#include <kdl/frames.hpp>
#include <tf_conversions/tf_kdl.h>
#include <opencv-3.2.0-dev/opencv2/opencv.hpp>

namespace conversions {
    // some self explanatory conversions!

    void RvecToKDLRot(const cv::Vec3d _rvec, KDL::Rotation &_kdl);

    void RvecTvecToKDLFrame(const cv::Vec3d _rvec, const cv::Vec3d _tvec,
                            KDL::Frame &_kdl);

    void KDLFrameToRvectvec(const KDL::Frame _kdl, cv::Vec3d &_rvec,
                            cv::Vec3d &_tvec);

    void RvecTvecToPoseMsg(const cv::Vec3d _rvec, const cv::Vec3d _tvec,
                           geometry_msgs::Pose &_msg);

    void Matx33dToKdlRot(const cv::Matx33d _mat, KDL::Rotation &_kdl);

    void KDLRotToMatx33d(const KDL::Rotation _kdl, cv::Matx33d &_mat);

    void PoseMsgToVector(const geometry_msgs::Pose in_pose,
                         std::vector<double> &out_vec);

    void PoseVectorToPoseMsg(const std::vector<double> in_vec,
                             geometry_msgs::Pose &out_pose);

    void PoseVectorToKDLFrame(const std::vector<double> &in_vec,
                              KDL::Frame &out_pose);

    KDL::Frame PoseVectorToKDLFrame(const std::vector<double> &in_vec);

    void PoseVectorToRvectvec(const std::vector<double> &in_vec,
                              cv::Vec3d &_rvec,
                              cv::Vec3d &_tvec);


    void QuatVectorToKDLRot(const std::vector<double> &in_vec, KDL::Rotation
    &out_rot);

    KDL::Rotation QuatVectorToKDLRot(const std::vector<double> &in_vec);

    void KDLFrameToVector(const KDL::Frame &in_pose,  std::vector<double> &out_vector);

    geometry_msgs::Pose KDLFramePoseMsg(const KDL::Frame &in_pose);

    KDL::Frame PoseMsgToKDLFrame(const geometry_msgs::Pose  &in_pose);

    void AxisAngleToKDLRotation(KDL::Vector axis, double angle, KDL::Rotation & out);
};

#endif //TELEOP_VISION_CONVERSIONS_HPP_HPP
