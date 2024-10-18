<center>

**nemusic**

C++ 的 GTK 音乐平台客户端

[![GPL v3 license](https://img.shields.io/badge/license-GPL_3-blue.svg)](https://raw.githubusercontent.com/suoyuan666/tlog/master/LICENSE)

</center>

---

本项目仅用于学习研究使用，请勿将本项目的任何内容用于商业或非法目的，否则后果自负。

---

#### Feature

- C++ 17 + [gtkmm](https://gtkmm.org/en/) 开发

#### TODO

- [ ] 将网络库更换成 asio
- [ ] 引入 ffmpeg
- [ ] 主题支持动态去色
- [ ] 支持网易云音乐
    - [ ] 账号登陆/签到
    - [ ] 歌词显示
    - [ ] 个人推荐相关的获取
- [ ] 支持 Mpris
- [ ] 支持 Meson 构建系统

#### 构建

项目目前依赖于 libcurl 和 libvlc，下一步准备要替换成 asio 和其他音乐播放的库（比如 SDL？之前好像看到貌似 SDL 支持音乐播放的功能）。

```bash
$ git clone --depth=1 https://github.com/suoyuan666/nemusic
$ cd nemusic
$ git submodule update --init
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build -j `nproc`
``` 