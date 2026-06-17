# RealSense Node Dev

The RealSense camera must be set to **slave mode** to receive the sync signal frequency via FSYNC.

## Hardware Sync Setup

Enable PWM output on the host to drive the sync signal:

```bash
sudo su
cd /sys/class/pwm/pwmchip3
echo 0 > export
cd pwm0
echo 33333333 > period    
echo 1000000 > duty_cycle
echo 1 > enable
```
## Verifying Sync

Once PWM is enabled and the camera is running, confirm it's locked to the sync signal:

```bash
v4l2-ctl --device=</path/to/camera/> --stream-mmap
```

Expected output — steady ~30 fps means the camera is locked to the external sync:\

If fps is erratic or significantly different from 30, check:
- PWM is enabled (`cat /sys/class/pwm/pwmchip3/pwm0/enable` should return `1`)
- The FSYNC wire is connected
- The camera sync mode is set to slave (`set_sync.cpp`)

    

For programmatic sync configuration, see [set_sync.cpp](realsense/set_sync.cpp)