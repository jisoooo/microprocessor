Team ``두번하조``
=======================

Members
--------
|순서 | 이름 | 학번 | 학과|
| ---------  | ----------- | --------------- | ------------------------ |
|     1      | 박연준 |  20150406| 산업경영공학과 |
|     2      | 김지수 |  20150863| 컴퓨터공학과 |
|     3      | 김성태 |  20150987| 컴퓨터공학과 |


How to Compile
-----------
 - Go to top directory
 - Command 'make' will build 'project' in Debug directory.
 - Command 'make clean' will erase 'project'
 - Thus type make in command line. 

How to Start Game
-------------------
 - Type 'sudo minicom -s' in command line
 - Type 'loady' in command line
 - Press 'Ctrl + A + S'
 - Select ymodem
 - Go to Debug directory where 'project' was made with 'make' command
 - Type bootelf in command line
 - Start Screen will appear

How to Play game
-------------------
  - Toucing direction button in monitor move pacman according to direction button
  - Eating bell will make enemy as crying victim so that pacman can eat them, which earn extra 200 points.
  - Eating seed will make extra 5 score for each seed
  - Eating life will earn extra life if the number of life was less than 3, otherwise just remain same as 3.
  - Meeting enemy will be resulted in one lost of life, which will disappear one heart image on the screen. 
  - Timer is set to 50. Therefore, after 50 seconds, the game over.
  - If pacman lost it's all lives, the game over. 
