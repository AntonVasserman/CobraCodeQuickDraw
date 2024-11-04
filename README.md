# Quick Draw (with C++)
This is a Repository for Quick Draw, a Game Project from Cobra Code's Udemy course.

As a challenge to practice and improve my C++ and Coding in Unreal Engine, this project is done using C++ rather than Blueprints.

## References

Cobra Code on Udemy: https://www.udemy.com/user/stephen-knall-2/ <br>
The Udemy Course: https://www.udemy.com/course/unreal-2d-course/

## Additional Features (not included in the course)

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

TODO:
1. Attack is done via a Combination of Buttons in an Order (Arrows in Keyboard / Facepad in Controller)
2. Added support for multiple enemies, specifically added minions to accompany the Toad Samurai (this results in a Ghost of Tsushima like duel)
3. Draw indicator improved by adding sound and draw animations
4. Added Score per enemy defeated
5. Added multiple levels with difficulty set by a Data Table with the Game Loop playing until player loses
6. Added Main Menu
7. Added persistence for score and high score
8. Added Sound & FX (Grayscale on defeat, and as rounds progress transition to afternoon vibe and night vibe)

Done: