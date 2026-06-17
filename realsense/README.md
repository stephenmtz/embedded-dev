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

For programmatic sync configuration, see [set_sync.cpp](realsense/set_sync.cpp)