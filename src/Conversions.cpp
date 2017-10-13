
#include <vector>

#include "custom_conversions/Conversions.h"

using namespace std;

void conversions::RvecToKDLRot(const cv::Vec3d _rvec, KDL::Rotation &_kdl) {
    cv::Matx33d mat;
    cv::Rodrigues(_rvec, mat);
    _kdl = KDL::Rotation(mat(0, 0), mat(0, 1), mat(0, 2), mat(1, 0), mat(1, 1), mat(1, 2),
        mat(2, 0), mat(2, 1), mat(2, 2));
}

void conversions::RvecTvecToKDLFrame(
        const cv::Vec3d _rvec, const cv::Vec3d _tvec, KDL::Frame &_kdl) {
    cv::Matx33d mat;
    cv::Rodrigues(_rvec, mat);
    _kdl.M = KDL::Rotation(mat(0, 0), mat(0, 1), mat(0, 2), mat(1, 0), mat(1, 1), mat(1, 2),
        mat(2, 0), mat(2, 1), mat(2, 2));
    _kdl.p.data[0] = _tvec.val[0];
    _kdl.p.data[1] = _tvec.val[1];
    _kdl.p.data[2] = _tvec.val[2];
}

void conversions::KDLFrameToRvectvec(
        const KDL::Frame _kdl, cv::Vec3d &_rvec, cv::Vec3d &_tvec) {

	cv::Matx33d mat;
    conversions::KDLRotToMatx33d(_kdl.M, mat);
    cv::Rodrigues(mat, _rvec );

    _tvec.val[0] = _kdl.p.data[0];
    _tvec.val[1] = _kdl.p.data[1];
    _tvec.val[2] = _kdl.p.data[2];

}

void conversions::RvecTvecToPoseMsg(const cv::Vec3d rvec, const cv::Vec3d tvec,
                       geometry_msgs::Pose &msg){

    KDL::Frame temp_frame;
    conversions::RvecTvecToKDLFrame(rvec,
                                    tvec,
                                    temp_frame);
    tf::poseKDLToMsg(temp_frame, msg);

}


void conversions::Matx33dToKdlRot(const cv::Matx33d _mat, KDL::Rotation &_kdl) {
    _kdl = KDL::Rotation(_mat(0, 0), _mat(0, 1), _mat(0, 2), _mat(1, 0), _mat(1, 1), _mat(1, 2),
        _mat(2, 0), _mat(2, 1), _mat(2, 2));
}


void conversions::KDLRotToMatx33d(const KDL::Rotation _kdl, cv::Matx33d &_mat) {
    _mat = cv::Matx33d(_kdl(0, 0), _kdl(0, 1), _kdl(0, 2), _kdl(1, 0), _kdl(1, 1), _kdl(1, 2),
        _kdl(2, 0), _kdl(2, 1), _kdl(2, 2));
}

void conversions::PoseMsgToVector(const geometry_msgs::Pose in_pose,
                                  vector<double> &out_vec) {

    out_vec.at(0) = in_pose.position.x;
    out_vec.at(1) = in_pose.position.y;
    out_vec.at(2) = in_pose.position.z;
    out_vec.at(3) = in_pose.orientation.x;
    out_vec.at(4) = in_pose.orientation.y;
    out_vec.at(5) = in_pose.orientation.z;
    out_vec.at(6) = in_pose.orientation.w;
}

void conversions::VectorToPoseMsg(const vector<double> in_vec,
                                  geometry_msgs::Pose &out_pose) {

    out_pose.position.x = in_vec.at(0);
    out_pose.position.y = in_vec.at(1);
    out_pose.position.z = in_vec.at(2);
    out_pose.orientation.x = in_vec.at(3);
    out_pose.orientation.y = in_vec.at(4);
    out_pose.orientation.z = in_vec.at(5);
    out_pose.orientation.w = in_vec.at(6);

}

void conversions::VectorToKDLFrame(const vector<double> &in_vec, KDL::Frame &out_pose) {
    geometry_msgs::Pose pose_msg;
    conversions::VectorToPoseMsg(in_vec, pose_msg);
    tf::poseMsgToKDL(pose_msg, out_pose);
}


void conversions::KDLFrameToVector(const KDL::Frame &in_pose,  vector<double> &out_vector){
    geometry_msgs::Pose pose_msg;

    tf::poseKDLToMsg(in_pose, pose_msg );
    conversions::PoseMsgToVector(pose_msg, out_vector);
}



void conversions::AxisAngleToKDLRotation(KDL::Vector axis, double angle, KDL::Rotation & out) {

    double c = cos(angle);
    double s = sin(angle);
    double t = 1.0 - c;

    //  if axis is not already normalised
    axis.Normalize();

    double m[3][3];

    m[0][0] = c + axis[0]*axis[0]*t;
    m[1][1] = c + axis[1]*axis[1]*t;
    m[2][2] = c + axis[2]*axis[2]*t;


    double tmp1 = axis[0]*axis[1]*t;
    double tmp2 = axis[2]*s;
    m[1][0] = tmp1 + tmp2;
    m[0][1] = tmp1 - tmp2;
    tmp1 = axis[0]*axis[2]*t;
    tmp2 = axis[1]*s;
    m[2][0] = tmp1 - tmp2;
    m[0][2] = tmp1 + tmp2;
    tmp1 = axis[1]*axis[2]*t;
    tmp2 = axis[0]*s;
    m[2][1] = tmp1 + tmp2;
    m[1][2] = tmp1 - tmp2;

    out = KDL::Rotation(m[0][0], m[0][1], m[0][2],
                        m[1][0], m[1][1], m[1][2],
                        m[2][0], m[2][1], m[2][2]);

}



geometry_msgs::Pose conversions::KDLFramePoseMsg(const KDL::Frame &in_pose){

    double qx, qy, qz, qw;
    geometry_msgs::Pose pose_msg;

    in_pose.M.GetQuaternion(qx, qy, qz, qw);
    pose_msg.position.x = in_pose.p.x();
    pose_msg.position.y = in_pose.p.y();
    pose_msg.position.z = in_pose.p.z();

    pose_msg.orientation.x = qx;
    pose_msg.orientation.y = qy;
    pose_msg.orientation.z = qz;
    pose_msg.orientation.w = qw;

    return pose_msg;
}



KDL::Frame conversions::PoseMsgToKDLFrame(const geometry_msgs::Pose  &in_pose){

    KDL::Frame frame;

    frame.p.x(in_pose.position.x);
    frame.p.y(in_pose.position.y);
    frame.p.z(in_pose.position.z);

    frame.M = KDL::Rotation::Quaternion(
        in_pose.orientation.x, in_pose.orientation.y,
        in_pose.orientation.z, in_pose.orientation.w);

    return frame;
}
