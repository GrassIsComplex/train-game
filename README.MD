# Train Game

## Overview
ty chatgpt for the readme
**Train Game** is a small, keyboard-only routing game set in a simplified metro station. Trains enter the station from the top and automatically travel downward through a grid of tracks and switches. Each train has a **destination track**, and your job is to **route it correctly using track switches** before it exits the station.

The challenge comes from timing and planning: switches must be set *before* trains reach them, and mistakes quickly lead to game over.

The game is intentionally minimal and deterministic, focusing on clarity, quick decisions, and escalating pressure rather than complex systems.

---

## Core Concept

* The station consists of multiple **vertical tracks**.
* Each track has several **switches** that can redirect a train:

  * Straight (no change)
  * Left (move to the track on the left)
  * Right (move to the track on the right)
* Trains spawn at the top on a random track and move downward automatically.
* Each train has a **destination track**, shown by its color.
* When a train exits the bottom:

  * Correct track → **score increases**
  * Wrong track → **mistake**
* Three mistakes ends the game.

---

## Visual Language

* **Train color** = destination track
* **Black switch** = straight
* **Purple switch** = left
* **Green switch** = right
* **Red circle** = cursor (current switch selection)
* **Colored blocks at the bottom** = track color reference
* **Red Xs** = mistakes

---

## Controls

### Cursor Movement

Move the selection cursor between switches:

* **Arrow Keys** or **WASD**

  * Left / Right: change track column
  * Up / Down: change switch row

The cursor wraps around at the edges.

---

### Switch Control

You can change the direction of the currently selected switch in two ways:

#### Cycle Direction

* **Enter**

  * Straight → Left / Right (contextual)
  * Left → Right
  * Right → Straight

#### Direct Direction (Advanced / Faster)

* **J** – Set switch to **Left** (if possible)
* **K** – Set switch to **Straight**
* **L** – Set switch to **Right** (if possible)

These allow faster, more deliberate routing once you are familiar with the layout.

---

### Game State

* **P** – Pause / unpause the game
* **Close window** – Exit the game

---

## Win / Lose Conditions

* **Score** increases for every correctly routed train.
* **Mistakes** increase for every incorrectly routed train.
* At **3 mistakes**, the game ends.
* When paused, trains stop moving and switches cannot be changed.

---

## Design Goals

* Keyboard-only gameplay
* Deterministic, predictable simulation
* Simple visuals with clear meaning
* High pressure from timing, not complexity
* Small scope suitable for a one-night project
