# 🎮 Gem Cascade (C++ Console Match-3 Game)

Welcome to **Gem Cascade**, a fully functional, console-based Match-3 puzzle game (inspired by Bejeweled and Candy Crush) written in **C++**. The game features custom UTF-8 graphics, visual animations, cascade physics, sound effects, and power-ups, all running smoothly inside the Windows command prompt.

---

## ✨ Features

- **Rich Text Graphics:** Uses ANSI escape codes and UTF-8 shapes to render a vibrant, colorful 8x8 game board.
- **Cascade & Gravity Physics:** Matches break away, causing the gems above to fall down dynamically, followed by new gems filling the board.
- **Chain Combos:** Triggering multiple matches in a single turn multiplies your score exponentially ($10 \times 2^x$).
- **Powerful Power-Ups:**
  - 💣 **Bomb:** Clears a $3 \times 3$ area around a chosen central piece (Cost: 120 points).
  - 🚀 **Rocket:** Clears an entire row or column of your choice (Cost: 100 points).
  - 💡 **Hint:** Scans the board to find and highlight the best available move (Cost: 70 points).
- **Auto-Shuffle:** Automatically shuffles and regenerates the board if no valid moves are left, ensuring the game never gets soft-locked.
- **Audio SFX:** Implements Windows Multimedia API (`winmm`) to play distinct sound effects for breaks, explosions, and rockets.
- **Save & Load System:** Save your high score and board state to pick up right where you left off.

---

## 🚀 Getting Started (Windows Only)

Since this project relies on Windows-specific headers (`<Windows.h>` and `<mmsystem.h>`) for handling color rendering and audio playback, it must be compiled and run on a Windows environment.

### Prerequisites
* A C++ compiler supporting C++11 or higher (e.g., MinGW/GCC or MSVC in Visual Studio).
* A terminal/command prompt that supports UTF-8 characters and ANSI color sequences.

### File Structure Setup
Make sure you have a `sounds` directory next to your compiled executable containing the following `.wav` audio files:
```text
├── GemCascade.exe
├── main.cpp
└── sounds/
    ├── glass-break.wav
    ├── explosion.wav
    └── rocket.wav
