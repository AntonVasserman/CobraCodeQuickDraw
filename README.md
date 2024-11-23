# Quick Draw (with C++)
This is a Repository for Quick Draw, a Game Project from Cobra Code's Udemy course.

As an exercise to improve my C++ in Unreal Engine, this project is done using C++ rather than only Blueprints.

In addition, as an exercise to improve my Game Programmering skills, this project includes:
* Refactorings: Different code structure and implementation of existing features
* New Features: Additions on top of the initial project to expand the gameplay

## References

Cobra Code on Udemy: https://www.udemy.com/user/cobra-code/

The Udemy Course: https://www.udemy.com/course/unreal-2d-course/

## Additional Features

### Refactoring:

1. Game-loop is handled via Phase Change Event instead of GameMode handling everything
2. Exclamation Mark moved to be a Widget instead of a Sprite Actor
3. Camera and Player Character are being initiated via PlayerStart instead of a Pawn/Character Blueprint in the level
4. Inputs as well as Widget are being handled via a PlayerController
5. AI is being handled via an AIController
6. Phase state moved into a GameState class
7. Enemy Attacks right after Player tries to attack too early
8. Changed Camera into Ortho mode

### New Features:

#### TODO:

1. Draw Button Combination in favor of single Draw Button
2. Multiple Enemies
3. Main Menu
4. Multiple Levels
5. Score and High Score
6. Final Polish: Additional Animations, Sounds, Music, and FX

<!--
#### Done:
-->
