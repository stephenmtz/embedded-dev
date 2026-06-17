#include <librealsense2/rs.hpp>
#include <cstdio>
#include <string>

int main() {
    rs2::context ctx;
    for (auto&& d : ctx.query_devices()) {
        std::string sn = d.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
        if (sn == "ENTER SERIAL NUMBER HERE") {
            auto s = d.first<rs2::depth_sensor>();
            s.set_option(RS2_OPTION_INTER_CAM_SYNC_MODE, 3); // setting the mode here MODE 3 is what the realsense needs to be in
            printf("camera %s sync mode now: %.0f\n",
                   sn.c_str(),
                   s.get_option(RS2_OPTION_INTER_CAM_SYNC_MODE));
            return 0;
        }
    }
    printf("target serial not found\n");
    return 1;
}

/*
    Single-camera utility. For multiple RealSense devices, loop over
    a list of serial numbers or configure sync mode via realsense_config.yaml.
*/