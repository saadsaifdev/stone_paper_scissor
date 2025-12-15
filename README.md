# Stone Paper Scissors Game (C++)

🎮 **Stone Paper Scissors** is an interactive **Rock-Paper-Scissors game** implemented in **C++**, designed to run in the terminal with **color-coded output**.  
This project demonstrates basic C++ programming concepts including **enums, structs, functions, loops**, and **random number generation**.

## Features
- 🆚 **Player vs Computer gameplay**: Challenge the computer in multiple rounds.
- 🔢 **Customizable rounds**: Choose how many rounds to play in each session.
- 🎨 **Color-coded results**:
  - 🟢 Green → Player wins  
  - 🔴 Red → Computer wins  
  - 🟡 Yellow → Draw
- 🏆 **Final winner** displayed after all rounds.
- 🔄 **Replay option**: Play multiple sessions without restarting the program.
- 🧩 **Clean code structure** using enums, structs, and functions for readability and maintainability.

## Technologies Used
- C++ (Standard Library)
- ANSI escape codes for terminal colors
- Random number generation with `<cstdlib>` and `<ctime>`

## How to Run
1. **Compile the program** using a C++ compiler:
```bash
g++ stone_paper_scissor.cpp -o stone_paper_scissor