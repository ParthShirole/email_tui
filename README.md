# 📧 email tui


---

</div>
<div align="center">


### Description
A *terminal-based email client*.

**Simple, basic and straight-forward.**

Created under Eklavya Mentorship Program 2021, SRA, VJTI.
</div>

---
### Table of Contents

- [Description](#description)
- [About This Project](#about-this-project)
- [Getting Started](#getting-started)
- [References/Notes](#referencesnotes)
- [Troubleshooting](#troubleshooting)
- [Contributors](#contributors)
- [Acknowledgements](#acknowledgements)
- [License](#license)


## About This Project

>sample snaps/recording
[![asciicast](https://asciinema.org/a/VMSOEFy6vlLuFr3DvQnK3efDQ.svg)](https://asciinema.org/a/VMSOEFy6vlLuFr3DvQnK3efDQ)

#### What is a _TUI_

In computing, text-based user interfaces (TUI) is a retronym describing a type of user interface (UI) common as an early form of human–computer interaction, before the advent of graphical user interfaces (GUIs). Like GUIs, they may use the entire screen area and accept mouse and other inputs. They may also use color and often structure the display using special graphical characters. The modern context of use is usually a terminal emulator.

To read more about tui, [click here.](https://en.wikipedia.org/wiki/Text-based_user_interface)

#### What is _Email_

Electronic mail (email or e-mail) is a method of exchanging messages ("mail") between people using electronic devices.

Email operates across computer networks, primarily the Internet. Today's email systems are based on a store-and-forward model. Email servers accept, forward, deliver, and store messages. Neither the users nor their computers are required to be online simultaneously; they need to connect, typically to a mail server or a webmail interface to send or receive messages or download it.



#### Technologies/Libraries Used

- *FTXUI*

  (A simple C++ library for terminal based user interface.)

  [link](https://github.com/ArthurSonzogni/FTXUI)

- *VMime*

  (A library offering all the features to build a complete mail client.)

  [link](https://www.vmime.org/)

#### Protocol/URL(s) used

* For Sending Mail
  - protocol used : SMTP
  - url : `smtp://smtp.gmail.com`

* For Fetching Mail
  - protocol used : IMAP
  - url : `imap://username:password@imap.gmail.com:993`


---

## Getting Started

### Prerequisites

#### FTXUI

```html
git clone https://github.com/ArthurSonzogni/FTXUI    
```


#### Vmime

```html
git clone https://github.com/kisli/vmime    
```


#### CMake
```html
sudo apt-get install cmake
```
OR

Refer https://cmake.org/

#### TOML++
```html
git clone https://github.com/marzer/tomlplusplus
``` 

Refer https://marzer.github.io/tomlplusplus/

---

### Installation

1. Clone this repo
```html
git clone https://github.com/ParthShirole/email_tui
```
### Usage

```html
mkdir build
cd build
cmake ..
make -j8
./ftxuistarter
```
---

## References/Notes

1. 
2.
3.

---

## Troubleshooting

>
>
---

## Contributors

</div>

<div align="center">

 Shreyas Atre - [@satacker](https://satacker.github.io/)

 Kunal Wadhwa - [@kwadhwa539](https://github.com/kwadhwa539)
 
 Parth Shirole - [@parthshirole](https://github.com/ParthShirole)
 
 

</div>

---
## Acknowledgements
- Special thanks to @ArthurSonzogni for his amazing UI library FTXUI
- Creators and contributors of Vmime Library
- SRA and Team (duh)

---
## License
```
```


[Back To The Top](#📧-email-tui)