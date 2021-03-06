#ifndef DETECTION_LIDAR_TRACKER_H
#define DETECTION_LIDAR_TRACKER_H

#include <ros/ros.h>
#include <detection/LidarRawArray.h>
#include <detection/Target.h>
#include <detection/TargetArray.h>
#include "detection/object.h"
#include "detection/GNN.h"

class LidarTracker
{
public:
    LidarTracker(void);
    ~LidarTracker();

    void KF(const detection::LidarRawArray& input);
    void InitTrack(const LidarObject &obj);
    void Predict(void);
    void MatchGNN(const std::vector<LidarObject>& src);
    void Update(const std::vector<LidarObject>& src);
    void RemoveTrack(int index);
    bool IsConverged(int track_index);
    void PubLidarTracks(void);
    void GetTimeStamp(ros::Time& stamp);
    void GetLidarTrack(std::vector<LocalTrack>& tracks);

private:
    std::vector<vector6d> X, X_;  // rx ry vx vy ax ay
    std::vector<matrix6d> P, P_;
    std::vector<ObjectInfo> track_info;
    matrix6d init_P;
    matrix6d F;
    matrix6d Q;
    matrix2_6d H;
    matrix2d R;

    std::vector<std::pair<int, int> > matched_pair;
    std::vector<bool> prev_matched;
    std::vector<bool> src_matched;

    double ts;
    ros::Time time_stamp;
};

#endif // DETECTION_LIDAR_TRACKER_H