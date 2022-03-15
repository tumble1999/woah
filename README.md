# WOAH
**W**ay **O**rganised **A**PT **H**andler - A wrapper for APT inspired by [YAY](https://github.com/Jguer/yay/)

**DEBIAN/UBUNTU ONLY*** - *This is a wrapper for APT and therefore is only available for Debian/Ubuntu systems.*

## Building
```
sudo apt install build-essential cmake apt-file libapt-pkg-dev
```
```
mkdir build
cd build
cmake ..
```
## Installing
Make sure you have [built](#Building) and then cd back to the main folder (`cd ..`).
```
sudo cpack --config build/CPackConfig.cmake
sudo apt install ./woah-0.0.0-Linux.deb
```

## Todo
Moved to https://github.com/tumble1999/woah/projects/1