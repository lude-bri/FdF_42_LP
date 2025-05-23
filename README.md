<!-------FdF_Image-------->
<a name="readme-top"></a>
<p align="center">
	<img src="https://capsule-render.vercel.app/api?type=venom&height=200&color=0ABAB5&text=FdF&fontAlign=50&fontAlignY=61&animation=fadeIn&fontColor=fcf3f2&fontSize=100" />
</p>

<!-------About-------->

## About

`FdF` is a fascinating project that transforms numerical matrices into beautiful 3D wireframe representations. Think of it as a digital cartographer that turns boring numbers into stunning topographic landscapes. This project combines mathematical elegance with graphical programming, all while adhering to the minimalist Unix philosophy.

<div align=center>
	<image src=img/japan-1.png>
	<image src=img/japan-2.png>
	<image src=img/japan-3.png>	
</div>

<!-------Index-------->

## <a name="#index-0">Index</a>

<ul>
	<li><strong><a href="#1-the-magic-of-isometric-projection" style="color:white">1. The Magic of Isometric Projection </a></strong></li>
	<li><strong><a href="#2-linear-algebra-behind-the-scenes" style="color:white">2. Linear Algebra Behind the Scenes </a></strong></li>
	<li><strong><a href="#3-pixel-by-pixel-drawing-basics" style="color:white">3. Pixel by Pixel: Drawing Basics </a></strong></li>
	<li><strong><a href="#4-bresenhams-algorithm-how-to-draw-a-line-in-a-computer" style="color:white">4. Bresenham's Algorithm: How to draw a line in a computer </a></strong></li>
	<li><strong><a href="#5-results" style="color:white">5. Results </a></strong></li>
</ul>

<div align="center">
<ul>
	<li><strong><a href="#usage"> # Usage of FdF #</a></strong></li>
</ul>
	</div>
 
-----------------------------------------------------------
---

# <a name="#index-1">1. The Magic of Isometric Projection</a>

Isometric projection is the visual trick that lets us represent 3D objects in 2D space while preserving dimensional accuracy. Unlike perspective projection (which mimics how human vision works, making distant objects appear smaller), isometric projection maintains parallel lines and uniform scale - the hallmark of technical drawings and classic video games.

### The Mathematical Sorcery</a>

The transformation from 3D coordinates (x,y,z) to 2D screen space (x',y') follows this elegant dance:

```c
x' = (x - y) * cos(θ)
y' = (x + y) * sin(θ) - z
```
Where θ is typically 30° (0.523599 radians), giving us that perfect 30-60-90 triangular ratio that makes the projection "feel" right.

### Why Isometric Rocks for FdF

**1. No Vanishing Points**: Unlike perspective projection, parallel lines stay parallel forever. This means: no complex perspective division calculations, Consistent scale across the entire map and it is perfect for technical representations.

Also, **2. Z-Axis Clarity**, the uniform scaling makes elevation changes (z-values) immediately visible:

```c
// Without this, height differences would be barely noticeable
z_scale = 0.2; // Experiment with this value!
```
And **3. Nostalgic Charm**: This is how classic games like Q*bert and early SimCity rendered their worlds. There's something magical about seeing your heightmap come to life in that distinctive diamond-pattern grid.

### Historical Context

The technique dates back to Renaissance technical drawings, but its computer graphics implementation became famous in 1982 when Sega's "Zaxxon" became the first arcade game to use isometric projection. For FdF, we're using the same principles those pioneers did - just with fewer color limitations!

>[!TIP]
True isometric projection follows a specific pixel ratio:
For every 2 pixels horizontal movement, you move 1 pixel vertical. This maintains the proper 30° angles. Actually, cosine/sine calculations handle this automatically, but it's good to know when debugging "squished" looking maps.

# <a name="#index-1">2. Linear Algebra Behind the Scenes</a>

Beneath the visual poetry of FdF's wireframe landscapes lies the rigorous scaffolding of linear algebra - not as dry equations in a textbook, but as living geometry that breathes three-dimensionality into flat matrices of numbers. This mathematical framework transforms our cold, numerical heightmaps into warm, pulsating topographies through a series of elegant spatial transformations.

At the core of FdF's engine lives vector space theory in ℝ³, where each (x,y,z) coordinate becomes a position vector dancing through transformations. The isometric projection that seems so simple in its final form:

x' = (x - y) * cos(θ)
y' = (x + y) * sin(θ) - z

Actually conceals sophisticated matrix operations. We can represent this transformation more formally as:
```
P = [ cos(θ)  -cos(θ)   0   ]
    [ sin(θ)   sin(θ)  -1   ]
```
This projection matrix P becomes the gateway between our 3D data and 2D screen space. When we multiply our position vector v = [x, y, z]ᵀ by P, we're performing:
```
v' = P · v = [ xcosθ - ycosθ ]
[ xsinθ + ysinθ - z ]
```
The true power emerges when we compose transformations. Consider how we:

* **Scale** the model to fit our window by multiplying by a scalar matrix S
* **Rotate** around axes using rotation matrices R_x, R_y
* **Translate** to center the view with offset vectors

These operations form a transformation pipeline:
```
v_final = P · S · R_y · R_x · v_original
```

Matrix multiplication's associative property lets us combine all transformations into a single composite matrix M = PSR, making rendering incredibly efficient - we calculate M once, then apply it to every point.

But the algebra goes deeper. Surface normals (vectors perpendicular to each face) become crucial for realistic shading. By computing the cross product of edge vectors:
```
n = (v₂ - v₁) × (v₃ - v₁)
```

we get normal vectors that interact with our virtual light source through the dot product:
```
brightness = n · l / (‖n‖ ‖l‖)
```
This simple calculation - essentially measuring the angle between vectors - creates those beautiful elevation-based color gradients that make mountains pop from valleys.

The camera controls in FdF are essentially linear algebra in motion:

* Zoom scales all position vectors
* Rotation applies orthogonal matrices
* Panning performs vector addition

Even Bresenham's line algorithm - the workhorse of wireframe drawing - relies on vector mathematics, using integer arithmetic to approximate the linear interpolation between points. But before going there, let's understand how do we draw a pixel!

# <a name="#index-1">3. Pixel by Pixel: Drawing Basics</a>

At the heart of every wireframe rendering lies a fundamental truth - all computer graphics, no matter how complex, ultimately reduce to placing individual pixels on a screen. In FdF, this pixel-level control becomes our paintbrush, allowing us to transform mathematical abstractions into visible art.

### The Canvas of Memory

MiniLibX provides us with an image buffer - essentially a rectangular array of pixels in memory. Each pixel is represented by a 32-bit integer where:

* 8 bits store red intensity (0-255)
* 8 bits store green intensity (0-255)
* 8 bits store blue intensity (0-255)
* 8 bits handle transparency (alpha channel)

The memory layout follows a strict linear sequence:
```
Pixel (0,0) | Pixel (1,0) | ... | Pixel (width-1,0) | Pixel (0,1) | ...
```
This linear array requires careful indexing to access any specific (x,y) coordinate.

But this is just the surface of something incredible: drawing. How this works? Well, normally is the graphical library that handles it (just like minilibx). But there is methods, algorithms to paint, to draw a line in a computer.

Placing individual pixels gives us ultimate control, drawing wireframes requires connecting these points efficiently. This is where Bresenham's algorithm enters the stage - a brilliant method that determines which pixels to illuminate when drawing straight lines between any two points, using only integer arithmetic for speed... but that's a story for our next chapter.

# <a name="#index-1">4. Bresenham's Algorithm: How to draw a line in a computer</a>

In computer graphics, a line drawing algorithm is an algorithm for approximating a line segment on discrete graphical media, such as pixel-based displays and printers. On such media, line drawing requires an approximation (in nontrivial cases). Basic algorithms rasterize lines in one color. A better representation with multiple color gradations requires an advanced process, spatial anti-aliasing.

Bresenham's line algorithm is a line drawing algorithm that determines the points of an n-dimensional raster that should be selected in order to form a close approximation to a straight line between two points. It is commonly used to draw line primitives in a bitmap image (e.g. on a computer screen), as it uses only integer addition, subtraction, and bit shifting, all of which are very cheap operations in historically common computer architectures. It is an incremental error algorithm, and one of the earliest algorithms developed in the field of computer graphics. An extension to the original algorithm called the midpoint circle algorithm may be used for drawing circles.

In the realm of computer graphics, drawing straight lines appears deceptively simple—until you realize displays are grids of discrete pixels while lines exist in continuous mathematical space. This fundamental tension birthed an entire class of line-drawing algorithms, with Bresenham's (1962) emerging as the elegant integer-based solution that conquered the problem without floating-point arithmetic.

### Bresenham's Brilliance

The algorithm operates on three key insights:

* Integer-Only Arithmetic: Uses decision parameters rather than floating-point calculations
* Incremental Error Tracking: Maintains an "error term" to determine when to step diagonally
* Octant Awareness: Handles all line slopes by considering eight directional octants

For a line from (x₀,y₀) to (x₁,y₁), it:

* Calculates Δx and Δy
* Initializes a decision parameter (p = 2Δy - Δx)
* Iteratively: Plots the current pixel, adjusts p based on whether it steps in x or both x and y, moves to the next pixel

### Why It Beats Naïve Approaches

Alternative methods like:

* DDA (Digital Differential Analyzer): Uses floating-point steps → slow
* Equation Solving: y = mx + b → rounding errors accumulate

Bresenham avoids these pitfalls through what we might call "mathematical judo"—using the line's implicit equation to derive an integer-based decision parameter.

You can see my implementation as follows:
```c
void	bresenham(t_mlx *win, t_point p1, t_point p2)
{
	float	x_step;
	float	y_step;
	int		max;

	init_zoom(win, &p1, &p2);
	if (win->view != 3)
	{
		isometric_view(&p1, win->view);
		isometric_view(&p2, win->view);
	}
	p1.x += win->shift_x;
	p1.y += win->shift_y;
	p2.x += win->shift_x;
	p2.y += win->shift_y;
	x_step = p2.x - p1.x;
	y_step = p2.y - p1.y;
	max = ft_max(ft_mod(x_step), ft_mod(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		pixel_draw(win, p1, p2);
		p1.x += x_step;
		p1.y += y_step;
	}
}
```

# <a name="#index-1">5. Results</a>
<div align=center>
	<image src=img/himalaya.png>
	<image src=img/42-fdf-1.png>
	<image src=img/42-fdf-2.png>
	<image src=img/42-fdf-3.png>
	<image src=img/42-fdf-4.png>
</div>

# Usage
## Setup & Compilation

1. Clone repository:

```sh
git clone git@github.com:lude-bri/FdF_42_LP.git
```

2. Go inside the project folder and run `make`:

```sh
cd FdF_42_LP
make
```

3. Choose the map

```c
./fdf my_maps/japan.fdf
```

### License

This work is published under the terms of <a href="https://github.com/lude-bri/42_Common_Core/blob/main/LICENSE.md">42 Unlicense</a>.

<p align="right">(<a href="#readme-top">get to top</a>)</p>



