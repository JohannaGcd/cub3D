## 28-10
Creation of repo and simply brainstorming on the subject notes + notes from watching other repos.

## 03-11

Watching [this](https://www.youtube.com/watch?v=NbSee-XM7WA&t=1505s&pp=ygUIRERBIGluIEM%3D) video I wanted to understand raytracing a little bit better by making another small game. This will also allow me to understand the graphical library a little better and improve fundamental skills for programming (experimenting and testing without having a guide or end result). 

I hope this will not take longer than one week. For today, I merely want to install the graphical library, open a window and have a gridline drawn based on a map.

## 04-11

Worked my way through. Program now can fill in the grid with a square and remove it if clicked again.
Thinking about the cursor I learned about static and dynamic images in mlx library. At the moment I have one image that I update and push to the screen but apparently you can also sort of have layers by having different images that you can push to the window. I would like to learn a little bit more about this so I don't have to constantly draw the entire image to the screen everytime the cursor moves.

Some things I would like to implement for next session:

- Adding a little round circle that follows the mouse.
- Adding another little circle that can be moved through the wasd buttons.
- Probably for session after; drawing a line between the two points.

Most likely I will learn about layering in tomorrows session!

## 05-11

In today’s session, a function was developed to blend multiple images into a single final image for display. This allows the program to combine background, tiles, and cursor images without redrawing or recalculating them each time. The current implementation successfully displays a movable square cursor controlled with the WASD keys. The function updates the cursor’s position by erasing its previous location and redrawing it at the new coordinates. There’s no handling yet for out-of-bounds movement, which can cause crashes.

Next Steps:

- Add a second movable cursor, controlled by the arrow keys.
- Implement a line connecting the two cursors once both are functional.
- Add boundary checks to prevent crashes when moving out of bounds.
- (Optional) Explore mouse-based cursor control once hardware and hand comfort allow.

## 09-11

Still writing with left hand. So I will be brief:
Made a cursor for the mouse and print it to screen. Very slow tho

Can probs be optimized a little by having one layer for the cursors and one for the grid. Now I have two layers for the cursors and I blend them together.

Also started with a function to draw a line between the two points. Currently function is called when pressing 'l' and then only the differences between the positions get printed.

## 11-11
REduced lag significantly by haing one layer (though still laggy). Draw line between points now works.
I still need to hold the previous variables so I can remove the old line.
EDIT: Line removes now

## 16-11
Some time has passed. A lot of code has been written over the past few days. Commit messages are not too great and no logging. it was abunch of experimenting with the DDA algrotihm. My code definitely does something, but not what it needs to do.

A failed attempt but I learned a lot in the process.

Most likely I will start again tomorrow with another DDA attempt from scratch. I want to use a better approach but not too sure how. I like doing things the hard way by trial and error. But that takes time and often also a toll on my mental health... we will see

## 17-11
Short session. Tired but thought about new approach for DDA. thinking that it will help to separate the x and y component of the ray more. Hopefully that will make sense along the way

## 18-11
Getting closer to a working project. Calculating length of ray correctly now. However wall collision is still a bit wonky. From what I can see there will always be 4 scenarios to take into account. Wall collision from left to right, from right to left, from up to down and from down to up.

## 19-11
!!!!!! Wall detection has been done! We can try to shoot a bunch of rays now maybe and then technically we can go to the next stage (which is the actual game)

## 21-11
Though buggy and very much not leak proof, I think it is time to abandon our [geometry game](../geometry_game) and start with a clean slate again. For today I think I could write a small readme for the (un)finished "game". Afterwards we will have to think what the next phase is going to be. I'm thinking of having a topdown map again with a player on screen that can move around with the wasd keys. You can then shoot a beam of rays with the arrow keys. My reasons for doing this in a whole other project is cause I made too many strange choices that if I have to correct them, I end up doing more work than rewriting with the new knowledge gained.

Some pointers I'd like changed in the new version:
- Keyboard cursor is just a small image of 10x10 pixels that gets pushed to the window without having to constantly merge background and foreground.
    although, then where do I keep the rays?
- Different files for all the relevant DDA functions.
- No more mouse cursor but clicking still creates a square.
- Events are handled by a `keyboard_event` and `mouse_event` that reroute to the correct function based on the keycode.
- An event that shoots 90 rays (from -45 to 45) and beams it to the top down map.
- Another event that creates a new window showing an image of what the beams give when converted to their height on the screen. (basically a single frame of the wolfenstein game).

While writing, I think it would also be cool to have a map editor. A "simple" program that takes in the dimensions (MxN) and allows you a basic painting option much like the [square on click function](../geometry_game/square_on_click.c). When exiting it saves the map created in a .txt file or something with `1` for a wall and `0` for no-wall.

## 23-11
I realise a day later I had not written a log. Basically started the ray\_shoot program by copying a bunch of functions from the geometry\_game and altering them to fit my the new requirements (somewhat).

## 24-11
Running out of time so I have not refactored the DDA file (justcopied it). But...
- Added wall collision.
- Added player movement.
- Added creating of walls.
- Added a very simple, one directional, ray shooter that shoots 90 rays.

I'm thinking of taking the mouse cursor as the direction for the rays but that might be a tad too much effort at this stage.

LOOK!!!!

<img width="408" height="234" alt="image" src="https://github.com/user-attachments/assets/c8b6b513-3907-4d61-b914-448a276f0407" />
<img width="576" height="304" alt="image" src="https://github.com/user-attachments/assets/45014a6b-a36f-4fbb-b566-780b828c4c6e" />

## 25-11
Encountering a small bug with wall collision. There will be a small gap between the user and wall if moving DOWN or RIGHT. I think understand why (it checks the next cell even though it is on the border) but I think I will leave it.
Apart from that, I fixed a small bug in wall collision for player movement

Then there was also simple refactoring; separating functions to their own files. Looking back at my DDA algorithm, I start to wonder whether I can find the time and energy to write a tutorial/explanation for it.

Now the big next thing is converting the rays to an actual 3D like image.

I want to find a way so that *long rays appear small* and *short rays appear big*.

From the top of my head that means:

`screenlength = SOMECONSTANT * (1 / ray_length)`

The biggest raylength will quite simply result in 0 pixels. But what if we divide by 0? What is the smallest ray length we are allowed? 
And how big does that make the screenline?

Then I want to draw them to the screen. Which means I have to split the line in two and have *one half shot up* and the *other half shot down*. 
I want this so my lines all have the same middle. Otherwise it will look like a weird skyline.

Omg would you look at that...
<img width="962" height="352" alt="image" src="https://github.com/user-attachments/assets/84fde246-8538-4e52-9c74-50f57fd5d040" />

For debugging purposes I kind of want to have another screen to visualize the wolfenstein engine realtime while I can still see and move around in the map to create walls etc.

So I want
- add another screen that visualizes the wolfenstein engine.
- add realtime movement to wolfenstein engine.
- add direction to wolfenstein engine.

After that I think we can honestly start the actual game.

For that we (more or less) would need:
- Map parsing (ugh...)
- Textures to N/E/S/W side of walls
- Sky and floor (texture)

## 27-11
Okay so I added movement and rotation. Instead of a second screen I created a toggle to switch between the minimap and the wolfenstein engine. It was all rather easy because I implemented an angle variable when writing the DDA algorithm.

- Movement now is weird. It still acts like a top down game. I will need to take the direction into account so that when you move forward in the wolfenstein engine you move forward from your POV and not the map.
- Color for depth! 
- Also the ray currently has a limit on max\_length that gets drawn on screen bigger than what I want. I should do something in the calc\_ray\_length like `if (i > 20) raylength = inf`

Added correct movement with direction taken into account.

Not very happy with the code. It is more based on trial and error and looks (and feels) very finnicky, especially with the wall detection. Again it might have to do with which tile gets checked when on the border of a gridline. But it (sort of) works!

## 28-11
Added background with ceiling and floor. Quite easy by drawing in out before drawing the lines from the engine. 

Color depth seems to be a bit more difficult as I want it to depend on the max iterations that the DDA algrotihm needed which forces me to change the code I think.

(wait not that doesn't make sense. You can have many iterations and still have a short line if the ray just happened to pass alot of gridlines)

I might need a structure like 
```
t_ray
{
    int length_in_pixels;
    int color;
}
```

Then I can also give the walls different colors depending on which side of the wall they hit.

## 30-11
Ugh... with my tail tucked between my legs I go back to the drawing board. For some reason, I'm annoyed by this so progress will probably go a bit slower for a while. Learning new things always takes more time and this is probably the most useful and essential tool of becoming a better programmer. Learning new concepts are like cleaning a really messy room. It can feel overwhelming and difficult to find a good starting points, but the only way to make progress is by doing it. If you pick up a few clothes everyday, you'll soon find the room much easier to clean. So, don't tell yourself you have to understand a topic, **try** to understand it. You may fall asleep, or get annoyed or feel stupid or whatever but one thing is for certain: _You will never understand new concepts if you never make an effort to understand them..._

###### With all that said and done, let's get drawing.
Adding textures seems difficult and I'm unsure whether I understand [this tutorial](https://lodev.org/cgtutor/raycasting.html#Textured_Raycaster). Perhaps gathering more information will help clarify things but for now, this is what I got from it:
- find out where the wall was hit on the gridline. If we hit a wall (positioned at map[15][15]) horizontally and exactly in the middle (so y = 15.5 and x = 15). That means we will need the middle vertical line of the corresponding texture.
- Translate that to the corresponding x-value of the texture.
- By calculating the length of the y-line, you can also translate the corresponding y-value of the texture (you can, just to test, also skip this for now and do a texture that has a different color for every x-value, but remains the same along the y-values)
<img width="1752" height="1008" alt="image" src="https://github.com/user-attachments/assets/f8163f0b-c4df-4cf3-a3ae-aa5625869530" />

**Something else I realised from this tutorial is that the maker removed his fisheye effect by having a plane instead of a point.**
<img width="1410" alt="image" src="https://github.com/user-attachments/assets/87557c4a-2957-49d6-88c4-e1f0bc1a7db1" />

I don't know what he does when the box is in fron of the plane. Maybe then you don't have to correct it and you can just use the total length (in red on the image above).

## 01-12
Progress is going to be slow. I absolutely hate this and my life feels miserable. I feel stupid and lazy.

Added the `mlx_xpm_file_to_image()` to `init_tex()`. Now that we have our image, we should be able to start altering our DDA algorithm however I much rather prefer to smoke weed at this point so I think I need to chill for a sec and do something else... 

Trying to implement stuff but honestly, I think I might have to rewrite the wolfenstein and DDA algorithm for this. Another time I say!

## 03-12
<p align="left">Continuing on the idea that I will have to rewrite the whole thing (well... the engine). Might as well start working on the "beta" version where I try to implement Norminette standards and a Map parser. Though, come to think of it. If I can try to implement this in the current version, I can be a lot surer of myself when writing the school version. 

Anyway, this is what I came up with when brainstorming on the engine. I think this should be doable in a day or two. </p>

## 04-12
Not overthinking things and just getting started implementing yesterdays plan into actual code. Doesn't look like much but it's a start. This is how progress happens. Don't beat yourself up and see if you can wotk on it a little when you have the time.
<img align="center" width="50%" alt="texture_renderer_flowchart_cub3d" src="https://github.com/user-attachments/assets/502c6202-af61-4f75-be3d-678eebc503d4" />

## 07-12
Ok ok ok, don't be mad. Something is happening but this shit is tricky as fuck and after an hour my brain is farting like crazy. We get something though its very tricky to say what that something is.

[... some of the devlog got lost due to force pushing...]

I worked through it and it looks alright now. I believe the grid image doesn't work too well cause it has too many pixels and too little definition so the gridlines look weird and wonky. If we take a lower resulution image we get something like this:

<img width="985" height="320" alt="image" src="https://github.com/user-attachments/assets/fbcfda3d-ed5b-4f82-908e-fae68d99d1e6" />

Some of the rendering looks wonky at times (especially when moving around). Some weird screen tearing I believe. Maybe this can be resolved by removing the fish-eye effect but I think most of it is due to the integer `step_size` skipping over various amount of pixels... oh... I just fixed it and that seemed to work.

Hmm yeah it works!!!! TIme to begin the real deal I guess.

## 20-12
The real deal. 

I'm not sure where to start. Currently I'm looking at what I got already and thinking about what I need to change. A lot of stuff I will simply have to rewrite so it fits the school42 standards (norminette & while loops instead of for loops). And stuff will now need to be checked for errors and exit cleanly. I also will have to change the code so that the window can be increased in size. Quite a lot it seems! However it seems most important I start with understanding what I will get from Joanna after her parsing and that I write down some brainstorm thoughts.

I still see some weird texture error bugs where sometimes the lines are blacked out. Also the fisheye effect is still here. Those are two things I want gone I guess.

Looking at Michmos' repository I realize I have quite a big journey ahead of me still. My textures look much worse and my game doesn't nearly run as smooth as his. Trying to keep it positive I guess the good news is there is a lot to learn still!

Stuff is overwhelming. I need to think small. What can I do today that will help me tomorrow?

- I can try to initialize my window and have it be resizeable, printing the dimensions to the terminal.
- I can take another look at my ray tracer and try to outline the train of thought by rewriting in pseudocode.
- I can hardcode a map for me to start working with.
- I can write a makefile that downloads and compiles a specific version of the minilibx for me to work with.

## 27-12
Wrote the Makefile so that I can start initializing. Rough start but a start nonetheless. Sometimes I simply have to remind myself that what I'm doing might not feel like actual progress (or it is very slow, finnicky and tedious) but I am helping the next version of myself who will sit down and start writing code.

## 28-12
AAAARGH I'm just writing code without having overview of the entire project. I really hope this won't bite me in the ass though it probably will. 

Just trying to make steps towards writing the raycaster. Creating structures, initializing data (naming seems to be difficult here) and trying to handle errors in init part so I can clean up nicely incase of errors. Not handling specific error codes yet which I might still have to do?

I realize I will have to use movement with `get_time_of_day()` to implement smooth movement independent from framerate. This will most likely only be important when hooking events but it is something to keep in mind.

Created a simple map to work with for raytracing.

The smartest thing to do next would be to create the first image with the raytracing. This will be a big chunk and should probably be split into smaller chunks. Again I think the smartest thing to do is to first create a function that "shoots a ray" and returns the distance from the player to the wall. This function needs a position (where the ray will be shot from) and a direction (where the ray is travelling towards). This will also require me to know what the dimension of a single grid spot is (I think just a range from 1 to 2) and a wall collision detector. 

## 29-12
Notes from Johanna:
``` c
//t_textures stores paths to 4 wall textures (NO, SO, WE, EA)

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textures;

// t_colors: Stores RGB values for floor and ceiling (separate r, g, b ints)
typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
}	t_colors;

// t_map: Stores map grid as char** array, dimensions, and player position
typedef struct s_map
{
	char	**	grid;
	int		x_row;
	int		y_col;
	int		player_x;
	int		player_y;
	char		player_dir;
}	t_map;

// t_cub3d: Main structure containing all parsed data and metadata flags
typedef struct s_cub3d
{
	t_textures	textures;
	t_colors		floor;
	t_colors		ceiling;
	t_map		map;
	int			metadata_flags;
}	t_cub3d;
```

I am very tired and hungover today so no big ballsy moves today. spent most of my time thinking about my nvim setup however it sparked some energy for aesathetics and readability so I wrote some descriptions and aesthetics for the cub3d.h file. Also added X11 events for mlx_hook() which I will get into more next time.
## 30-12
Pffff another day of what seems like small progress. But I actually did alot! I wrote alot of descriptions and refactored much of the header for readability. I also learned a bit about masking and events from the X11 library which admittedly is still very daunting and confusing. I have some ideas on how to make movement smoother (which I haven't developed yet) but when pressing a key you usually get `a` (pause) `aaaaaaaaaaaaaaaaaaaa` which will make movement feel janky. I can fix this by having an event once the key is pressed and once the key is released and having a game loop that simply renders every frame. BUt this is for another time.

## 31-12
Right I want to have a look at the raytracer part since ultimately this is the singular thing I do 100% without Johanna. I am going to look at what I wrote last time and try to recapture my thoughts.

First thing I see. I had a t_ray structure:
```c
typedef struct	s_ray {
	double	ray_length;
	int		pixel_length;
	e_side	side;
	double	pos_wall_hit;
}	t_ray;
```

Now on to the function itself. [code from ray_shooter_alpha](../alpha_and_beta_cub3d/ray_shooter_alpha/src/calc_ray_with_tex.c). For reference also below:

Definition of variables:
```c
double  dx_dy[2];
```
dx and dy are the direction of the ray in respectively its x and y direction. If a ray was shooting directly upwards (angle is 90 degrees or 1/2 Pi) it would only travel in the x direction. Thus x would be 1 and y would be 0. These directional values are based on the unit circle. This isn't second nature to me but they're familiar enough to work with. What is important to know is that *for a specific ray these are constant*.

```c
double  dsx_dsy[2];
```
Imagine a grid with any line drawn through it. (oh dear god help) (you can ignore the really long red and really long green line) I drew them automatically cause _triangles are my favorite shape_ (SO to Alt J).
<img width="1343" height="608" alt="image" src="https://github.com/user-attachments/assets/66771757-791a-46f6-879b-da6cae1513cf" />

Can you see the red and green line following the blue line? `dsx` is the length of the ray when it **hits a vertical line** (the red line) and `dsy` is the length of the ray when it **hits a horizontal line** (the green line). I hope the drawing skills are able to form a triangle between `dsx` and `nxt_x` and respectively between `dsy` and `nxt_y`. We love triangles cause they adhere to trigonometry. For advanced readers you might be able to understand the use of knowing the angle.

```c
double  nxt_xy[2];
```
This is simply the distance to the next x or y gridline (respectively vertical or horizontal). Often these will be 1 in our iteration. I hope you can figure out why (hint: what happens if we hit a gridline?). It is important to note here what direction the ray is travelling since at any point there is a gridline to the right and to the lefft (and up and down) and we need to know which of those we are travelling towards.

```c
double  result;
```
Well the function is called `calc_ray_with_tex` so take a wild guess what this variable is for.

**On to the execution!** We start with a simple while loop that iterates for a maximum of 30 times. This is simply to prevent that, if we do not hit a wall, we don't iterate for ever. Otherwise the loop will break simply by hitting a wall and then the `break` function gets called.

We start by calculating the following (I'll explain what this is in a bit).
```c
nxt_xy[0] = -1 * fmod(x, 1);
		if (nxt_xy[0] == 0)
		{
			nxt_xy[0] = 1;
			if (dx_dy[0] < 0)
				nxt_xy[0] = -1;
		}
		else if (dx_dy[0] > 0)
			nxt_xy[0] = nxt_xy[0] + 1;
```
We constantly calculate some part for x and some part for y. You can see how similar above code block is with the one below.
```c
nxt_xy[1] = -1 * fmod(y, 1);
		if (nxt_xy[1] == 0)
		{
			nxt_xy[1] = 1;
			if (dx_dy[1] < 0)
				nxt_xy[1] = -1;
		}
		else if (dx_dy[1] > 0)
			nxt_xy[1] = nxt_xy[1] + 1;
```

Basically what we are doing here is trying to figure out where the next grid line is from our current position.

A `dx_dy` is used in this section so perhaps I should explain a little where these come from:
```c
	dx_dy[0] = cos(angle);
	dx_dy[1] = -sin(angle);
```
These come from the unit circle (google it). A small difference is the minus sign in the sinus. This has to do with the fact that the y-axis in our game is flipped. The mlx library considers the first pixel to be in the upper left corner. Thus our y-axis starts counting from top to bottom (which in normal cartesion coordinates (again google it, but it's not that important) is from bottom to top). We count the other way around so we need to use a minus sign to convert everything back to "standard mathematics".

Good! Now that that is out of the way we can try to simplify these two blocks of code into a singular function!
```c
double  calc_next_gridline(double pos, double dir)
{
    double  result;
    
    result = -1 * fmod(pos, 1);     //if pos = 12.2 then the next line is either -0.2 or 0.8
    if (result == 0)                //When we are on a gridline already the next line should be either 1 or -1
    {
        result = 1;
        if (dir < 0)
            result = -1;
    }
    else if (dir > 0)
        result += 1;                // -(0.2) + 1 = 0.8 (We have established which line is the next line with consideration of the direction of the ray.
    return (result);
}
```

Now we know the distance to the next gridlines we will at some point pass (if we do not hit a wall that is).

Remember that ray we are following? Well now we want to see what the distance of the ray is when we have hit the x-gridline, and respectively what distance of the ray is before we hit the y-gridline. I won't go into to much detail here either but we use pythagoras theorem to calculate this.

```c
dsx_dsy[0] = nxt_xy[0] / dx_dy[0];
dsx_dsy[1] = nxt_xy[1] / dx_dy[1];
```
The nice thing here is that dx and dy are also the angle of the ray with respect to the x or y axis (this is because of the unit circle).

So the next thing is the very principle of the raycasting. We want to compare the **length** of `dsx` and `dsy`. (note that distance can be negative as it has a direction but in my terminology, length is simply the size of the distance without direction and therefore always positive). This is why we use `fabs(dsx)` and `fabs(dsy)`.

The principe is as follows. whichever gridline (either horizontal or vertical) we pass first, is the one we will travel towards. Again, a visualization would be incredibly useful but my own imagination will have to do for now.

I'm sure you can see that the following codeblocks are again, very similar:
<table>
    <tr>
        <td>dsy is smaller</td><td>dsx is smaller</td>
    </tr>
    <tr>
        <td>
			
	result += fabs(dsx_dsy[1]);
	y += nxt_xy[1];
	x += (dsx_dsy[1] * dx_dy[0]);
	if (detect_wall_hori(dx_dy[1], (int) x, (int) y, data))
	{
		if (dx_dy[1] > 0)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
		ray->ray_length = result;
		ray->pos_wall_hit = x - floor(x);
		ray->pixel_length = convert_to_vert_line(ray->ray_length);
		break ;
	}		
</td>	
<td>
	
	result += fabs(dsx_dsy[0]);
	x += nxt_xy[0];
	y += (dsx_dsy[0] * dx_dy[1]);
	if (detect_wall_vert(dx_dy[0], (int) x, (int) y, data))
	{
		if (dx_dy[0] > 0)
		ray->side = EAST;
		else
			ray->side = WEST;
		ray->ray_length = result;
		ray->pos_wall_hit = y - floor(y);
		ray->pixel_length = convert_to_vert_line(ray->ray_length);
		break ;
	}			
</td>	
</tr>	
</table>

Well, there are some differences here. Particularly in the naming of NORTH, SOUTH, EAST, WEST. We also have two different functions being called (detect_wall_vert and detext_wall_hori. This makes it annoying to simplify. But in essence these two codeblocks do the same.

First we add the length of our ray (to the next and closest gridline) to our result. This is what raycasting is. Instead of following the ray bit by bit (which in theory would be inifinitesimely small) (love that word), we simply do it every time we pass a gridline since our walls can only be starting (and ending) at a gridline. They are in essence a square in our map, always filling an entire block (So x; 12-13 and y: 15-16 would be a block at position (12,15), (12.16), (13,15) and (13,16). Gosh visualization would be nice here).

Next we must update our x and y coordinates since we have now followed the ray to a new position. In the first scenario (where dsy is smaller) our y coordinate is now on the gridline. Thus we only need to add `nxt_y` to our current y-coordinate and voila!

Its respective coordinate (in the first scenario this is the x-coordinate), is a little more tricky. Again we use pythagoras theorem and the pythagorean identity (or SOHCAHTOA).
```
    Opposite/adjacent = Hypothenuse * sin/cos (angle)
```
(This seriously only makes sense after you draw everything out. Which is why I started with the [geometry_game](../alpha_and_beta_cub3d/geometry_game).

Because we used the unit circle our `dx` and `dy` are respectively `cos(angle)` and `-sin(angle)`

Next up is:
```c
	if (detect_wall_hori(dx_dy[1], (int) x, (int) y, data))
```
which is another part of code I won't discuss in detail currently but basically we want to see if we have hit a wall at the gridline (since we will only find walls at the gridlines).

If we **have** hit a wall then we technically are done. We have found a wall and we no longer need to continue or ray. However we will have set a couple of variables for our `t_ray` structure so that we can correctly calculate the textures later on.

First things first is which side of the wall we have hit. Since, if we have hit a vertical gridline, we could have hit it from the right or from the left. These are both different sides that can have different textures. We know which side by looking at what direction (in either x or y) our ray is travelling in.
``` c
if (dx_dy[0] > 0)
    ray->side = EAST;
else
	ray->side = WEST;
```
The following three assignments are somewhat straightforward.
```c
ray->ray_length = result;
ray->pos_wall_hit = y - floor(y);
ray->pixel_length = convert_to_vert_line(ray->ray_length);
```
`pos_wall_hit` is the position on the wall (which can be any float between 0.0 and 1.0). A simple modulus will do -> `fmod(12.45, 1) = 0.45`

I think I used AI here which is why I got `12.45 - floor(12.45) = 12.45 - 12 = 0.45`. But it might also have to do with the fact that 13.0 can both be the beginning of a texture as the end of a texture. Not too sure about this...

the `pixel_length` basically is the next step of raycasting and is a (rather simple) conversion of a ray, to a vertical stripe to project on your screen. The longer the ray, the smaller the vertical stripe.

Well... That is it for now I think! See you in the next year :)

## 02-01
Simply put I rewrote a lot of my previous entry in to actual code. One of the biggest contributing factors was writing a `ray_utils` structure that holds all variables I like to use in my `calc_ray_length_with_tex` function (I renamed this to `shoot_ray` in the newer version)

## 03-01
With the ray casting more or less done.  (at least the prototype) It's time to put it to the test. I don't need to draw anything on screen just yet. A simple terminal IO will do. Which first means I will have to see where I call the command in regards to the main loop.

For some reason the raycaster is not working completely as expected. I wrote some code to test with in `mock_parser` that can be deleted once the parser is completed by Johanna. This function file is my "lab" where I need not worry about norminette or any other issues since it will all be deleted when the actual parser is here.

Will have to look at the code another time however :( No idea as to why it is not working. My implementation seems sound so I think it is merely a small typo in the code.

## 04-01
Fixed a small but annoying bug. When rewriting my code on the second of Januari I must have fallen asleep cause I swapped X and Y in some calculations. Some simple print statements for the intermediate calculations showed where the error took place. Really happy to have fixed this bug with the resistance I felt for working on a Sunday evening but this should significantly impact tomorrows working hours!

## 05-01
From what I can see, raycasting works. There is a small point of attention what happens when the player is next to a wall since our current DDA might glitch/noclip through the wall but I will leave this when dealing with wall collision after the player movement has been implemented. Thus for now I would say the most important part is **creation of images** and **loading of textures** so we can get something on the screen with our raycasting. 

Ok after a little while I got most mlx functions in the project working. I still have to load the textures but the our main frame seems to work. You can check because when you run the program, you see a pretty big red square on the screen. This was done by pushing the image (mainframe) to the window.

Next is probably loading the textures. I'll see if I can quickly upload some xpm files for this.

## 06-01
Textures have been loaded in so we should be able to continue with the raycasting now and get our first official frame. This is quite some code but if we can fix this today I will save myself significant amounts of effort next session!

So, just to do some brainstorming. What I want in the end is a function called `render_frame`. It will need to have pretty much all data imaginable. The `mlx_data` for putting the final image to the window, the `cub3d` structure for the textures, the `level` structure for the map and the player position.
Then we should do something along the following:
```c
for (i in WINDOWWIDTH)
{
    shoot_ray in FOV;   //This will need to know the users direction
    draw_texture_line;  //This will need the texture, the image to draw on and the ray to calculate from.
}
put_image_to_window;
```
Looks pretty simple right?

Weeeeelll I mean yes sure in a way. But we first need to know in what direction we need to shoot our ray. Let's say we want an FOV of 90 degrees. That means that we will need to shoot a ray for every pixel in our window_width and give it the direction of our user minus (or plus) the offset so that we get the correct FOV direction for that specific ray with respect to our user's current direction. So to put some numbers to these abstract ideas, let's say our user is looking completely to the right (direction = 0). Then the ray representing the most left (first) row on our screen will have a direction of -45 degrees. and the ray representing the most right (final, if you count from left to right) will have a direction of 45 degrees. 

To draw the texture correctly we need to know a bunch of other stuff first too! 
I used a bunch of code from my previous attempt at writing this function so take a look at that (or not)
(`draw_textured_line`)

## 07-01
Easier said than done but we have something on screen!
<img width="1916" height="1122" alt="image" src="https://github.com/user-attachments/assets/7f406912-a99f-4a8c-80b4-dc18776a099b" />

Added colors now using a function that creates our RGB integer from the separate rgb values. Not much exciting stuff but it needs to be done at some point so why not now.
Also real quickly trying to fix the fisheye effect. DONE

Well... our time is almost up. It seems next up will be movement and wall collision and then at the end cleaning up.
- [ ] Creating gameloop with frame rendering (and FPS)
- [ ] Creating smooth movement based on key_pressed/key_released and framerate
- [ ] Creating wall detection
- [ ] Cleaning up the program.
- [ ] Cleaning up in case of errors.
- [ ] Creating minimap (for bonus)

I let AI draw a (very buggy) game loop just so I could move around to test the raycasting. The textures are still fucked and I now consider this a bug I need to fix. What is wrong I do not yet know but I'll find out :)
<img width="1933" height="1130" alt="image" src="https://github.com/user-attachments/assets/23539375-f22d-49ca-8550-a66706c00959" />

Creating the gameloop is going to take a while. From what AI wrote, I will have to do some brainstorming again to be able to make my own implementation. Yeeeeeeeeh....

I expect this to take 1 to 2 weeks depending on how much headspace I will have.
## 09-01
Fresh and ready to get started! My mind is set on the player movement. There are multiple aspects of it, especially since I want to do it ever so slightly different with continious rendering (rendering even when we're not moving) instead of static rendering (only update the screen if necessary).

With the todolist from yesterday in mind, I should probably start with remaking the todo list in more detail.

The first part is thinking of the game loop. The idea is that we continuously render frames and every time we render the frame we check if our player has moved, if yes we update the position and start rendering the frame.

```c
{
    update_player_position();
    render_frame();
}
```

Sounds easy right? Well it kind of is. We just have to think a little different. Let's think of the following two scenarios. We have a beefy computer that easily runs the game on 30 fps (frames per second) and another one that has a bit more trouble and only runs at 15 fps.

Our first computer is able to draw 30 frames per second, thus it "updates" the screen (draws a new frame) every 1/30th of a second. If we want to move at a constant speed, we will have to multiply our player's velocity with a time. (remember velocity is in meter per second. Multiplying by a time gives us the distance (v = ds/dt) -> ds = v * dt). Well what is dt in this case? You guessed it! The time passed from our previous frame; In coding time this is equivalent to `game.current_frame_time - game.previous_frame_time`. In the second scenario the calculation is exactly the same only this time the time between the frames will be bigger (since this time we only render a frame every 1/15th of a second). This way we have smooth movement regardless of framerate. (of course, the less fps we have the slower/janky the game will feel).

So, in `update_player_position()` we will have:
```c
update_player_position()
{
    get_current_time;
    delta_t = current_time - previous_time;
    if (game.key.w == 1)
        move_forward();
    if (game.key.s == 1)
        move_backward();
    if (game.key.a == 1)
        move_left();
    if (game.key.d == 1)
        move_right();
    if (game.key.left == 1)
        rotate_left();
    if game.key.right == 1)
        rotate_right();
    
    previous_time = current_time;
    return ;
}

//The basic idea of moving.
//DEGR_DIR is a constant that is dependent
//on the direction of movement
// (for example backwards would be 180degrees,
//to the left = 90 and to the right 270)
move_ANY_DIRECTION(player, delta_t)
{
    new_x = player.x + (cos(player.dir + DEGR_DIR) * VELOCITY * delta_t);
    new_y = player.y + (sin(player.dir + DEGR_DIR) * VELOCITY * delta_t);
    
    if (check_wall_collision(new_x, new_y, map) == false)
    {
        player.x = new_x;
        player.y = new_y;
    }
}
```
Hope that makes some kind of sense.

Ooooohkay, I now have the game loop sort of working so we should be able to slowly implement movement.

Pfffffffffffffffffffffffffffffffffffffffffffffff. Three hours later but we're on our way. I have the gameloop and our events. I just need to calculate the new player positions and check for collisions.

## 10-01
Massive brainfog today. Found a BUNCH of bugs which seem to question as to whether I was on the right track.

Image seems to be flipped; In our current test map we are looking upwards (north) and we should have a wall directly to our left. However, it is directly to our right.
Also, when changing the textures to something a little less visual and more eligible (like textures with words on them) I see that on the one side they are flipped (so NO would show everything correctly but then SO would have it flipped and vice versa. Same counts for WE/EA)

Rendering of textures goes haywire when I get too close to the walls. And don't even get me started on the hooking for movement. That shit is super super weird (a lot of hazzle with parsing delta_t_ms as a long????) I wish I could understand this stuff but it would be outside of the scope.

I'm starting to wonder whether to switch back to static rendering since that makes this hooking easier....

I am going to take a break for the next two days. I hit a wall and need some time to recharge.

Oh the mirroring must be due to a miscommunication in shoot ray and draw_walls! I am drawing the most left column on my screen when shooting the most right ray!

## 13-01

On the mirroring of the images; I have to remember that my gridline will be from 0 to N but from the other side from N to 0. So I will always have one side mirrored with my current implementation!
<img width="1111" height="1153" alt="image" src="https://github.com/user-attachments/assets/e4b914e0-8379-4a5a-af5b-1c100e97a14d" />

Whereas the other side will have:
<img width="1292" height="1331" alt="image" src="https://github.com/user-attachments/assets/6bd14897-e13c-4c93-953a-492979466dfa" />

Another bug to think about is when we are next to the wall; we clip through the wall and thereby try to render textures that are out of bounds. This image sums it up pretty well for myself:

<img width="612" height="499" alt="image" src="https://github.com/user-attachments/assets/98b3531a-43bf-49ed-aad6-cda4c5cb6c24" />

## 14-01

I mentioned this earlier I believe but my whole screen is flipped. It had something to do with how I was shooting rays and something mathematical. Okido I think I remember. When I am shooting the rays I count clockwise, but in my map I count counter clockwise. 
