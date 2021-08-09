# WOAH
**W**ay **O**rganised **A**PT **H**andler - A wrapper for APT inspired by [YAY](https://github.com/Jguer/yay/)

**DEBIAN/UBUNTU ONLY*** - *This is a wrapper for APT and therefore is only available for Debain/Ubuntu systems.*

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
Make sure you have [built](#Building)
```
sudo cpack --config build/CPackConfig.cmake
sudo apt install ./woah-0.0.0-Linux.deb
```

## Todo
- [x] -h - help
- [x] -V - Version
	- [x] -Vh - Version help
	- [x] -Vq - Version quiet
	- [x] -V apt - Version apt
	- [x] -V dpkg - Version dpkg
	- [x] -V apt-file - Version apt-file
	- [x] -V woah - Version WOAH
- [ ] -D - Database
	- [ ] -Dh - Database help
	- [ ] -Db - Database dbpath
	- [ ] -Dk - Database check
	- [ ] -Dq - Database quiet
	- [ ] -Dr - Database root
	- [ ] -Dv - Database verbose
- [ ] -F Files
	- [ ] -Fh - Files help
	- [ ] -Fb - Files dbpath
	- [ ] -Fl - Files list
	- [ ] -Fo - Files owns
	- [ ] -Fq - Files quiet
	- [ ] -Fr - Files root
	- [ ] -Fs - Files search
	- [ ] -Fv - Files verbose
	- [ ] -Fx - Files regex
	- [ ] -Fy - Files refresh
- [ ] -Q - Query
	- [ ] -Qb - Query dbpath
	- [ ] -Qc - Query changelog
	- [ ] -Qd - Query deps
	- [ ] -Qe - Query explicit
	- [ ] -Qg - Query groups
	- [ ] -Qi - Query info
	- [ ] -Qk - Query check
	- [ ] -Ql - Query list
	- [ ] -Qm - Query foreigon
	- [ ] -Qn - Query native
	- [ ] -Qo - Query owns
	- [ ] -Qp - Query file
	- [ ] -Qq - Query quiet
	- [ ] -Qr - Query root
	- [ ] -Qs - Query search
	- [ ] -Qt - Query unrequired
	- [ ] -Qu - Query upgrades
	- [ ] -Qv - Query verbose
- [x] -R - Remove
	- [x] -Rh - Remove help
	- [ ] -Rb - Remove dbpath
	- [ ] -Rc - Remove cascade
	- [ ] -Rd - Remove nodeps
	- [ ] -Rn - Remove nosave
	- [ ] -Rp - Remove print
	- [ ] -Rr - Remove root
	- [ ] -Rs - Remove recursive
	- [ ] -Ru - Remove uneeded
	- [ ] -Rv - Remove verbose
- [x] -S - Sync
	- [x] -Sh Sync help
	- [ ] -Sb Sync dbpath
	- [ ] -Sc Sync clean
	- [ ] -Sd Sync nodeps
	- [ ] -Sg Sync groups
	- [ ] -Sh Sync info
	- [ ] -Sl Sync list
	- [ ] -Sp Sync print
	- [ ] -Sq Sync quiet
	- [ ] -Sr Sync root
	- [x] -Ss Sync search
	- [x] -Su Sync upgrades
	- [ ] -Sv Sync verbose
	- [ ] -Sw Sync downloadonly
	- [x] -Sy Sync refresh
- [ ] -T - Deptest
	- [ ] -Th - Deptest help
	- [ ] -Tb - Deptest dbpath
	- [ ] -Tr - Deptest root
	- [ ] -Tv - Deptest verbose
- [ ] -U - Upgrade
	- [ ] -Uh - Upgrade help
	- [ ] -Ub - Upgrade dbpath
	- [ ] -Ud - Upgrade nodeps
	- [ ] -Up - Upgrade print
	- [ ] -Ur - Upgrade root
	- [ ] -Uv - Upgrade verbost
