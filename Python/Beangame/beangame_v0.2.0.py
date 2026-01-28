from tkinter import *
import math
import time

# ---------- CONFIG ----------
WINDOW_WIDTH = 1000
WINDOW_HEIGHT = 650
SIZE = 100            # Triangle size
PIXEL_SIZE = 5        # Pixel size
SPEED = 5             # Movement speed
ROTATION_SPEED = 90  # Degrees per second

# ---------- INITIAL STATE ----------
x1, y1 = 300, 250  # Green triangle
angle1 = 0
keys1 = set()

x2, y2 = 600, 250  # Red triangle
angle2 = 0
keys2 = set()

x3, y3 = 450, 250  # Blue triangle
angle3 = 0
keys3 = set()

last_time = time.time()

# ---------- WINDOW & CANVAS ----------
window = Tk()
window.title("BeanGameAlphaTriangles v0.2")
canvas = Canvas(window, width=WINDOW_WIDTH, height=WINDOW_HEIGHT, bg="black")
canvas.pack()

points = [(0, SIZE), (SIZE, SIZE), (SIZE // 2, 0)]  # Triangle relative points

# ---------- FUNCTIONS ----------
def rotate_point(px, py, cx, cy, angle_rad):
    dx = px - cx
    dy = py - cy
    rx = dx * math.cos(angle_rad) - dy * math.sin(angle_rad)
    ry = dx * math.sin(angle_rad) + dy * math.cos(angle_rad)
    return cx + rx, cy + ry

def point_in_triangle(px, py, tri):
    """Barycentric method to check if a point is inside a triangle"""
    (x0, y0), (x1, y1), (x2, y2) = tri

    det = (y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2)

    if det == 0:
        return False  # Degenerate triangle

    a = ((y1 - y2) * (px - x2) + (x2 - x1) * (py - y2)) / det
    b = ((y2 - y0) * (px - x2) + (x0 - x2) * (py - y2)) / det
    c = 1 - a - b

    return 0 <= a <= 1 and 0 <= b <= 1 and 0 <= c <= 1

def get_triangle_coords(x, y, angle):
    angle_rad = math.radians(angle)
    cx = x + SIZE / 2
    cy = y + SIZE / 2
    coords = []
    for px, py in points:
        wx = x + px
        wy = y + py
        rx, ry = rotate_point(wx, wy, cx, cy, angle_rad)
        coords.append((rx, ry))
    return coords

def draw_pixels():
    canvas.delete("all")  # clear canvas fast

    tri1 = get_triangle_coords(x1, y1, angle1)
    tri2 = get_triangle_coords(x2, y2, angle2)
    tri3 = get_triangle_coords(x3, y3, angle3)

    # Compute bounding boxes individually
    min_x1 = int(min(p[0] for p in tri1))
    max_x1 = int(max(p[0] for p in tri1))
    min_y1 = int(min(p[1] for p in tri1))
    max_y1 = int(max(p[1] for p in tri1))

    min_x2 = int(min(p[0] for p in tri2))
    max_x2 = int(max(p[0] for p in tri2))
    min_y2 = int(min(p[1] for p in tri2))
    max_y2 = int(max(p[1] for p in tri2))

    min_x3 = int(min(p[0] for p in tri3))
    max_x3 = int(max(p[0] for p in tri3))
    min_y3 = int(min(p[1] for p in tri3))
    max_y3 = int(max(p[1] for p in tri3))

    # Compute overall bounding box efficiently
    min_x = min(min_x1, min_x2, min_x3)
    max_x = max(max_x1, max_x2, max_x3)
    min_y = min(min_y1, min_y2, min_y3)
    max_y = max(max_y1, max_y2, max_y3)

    step = PIXEL_SIZE

    # Precompute triangle sets to reduce calls to point_in_triangle
    tri1_pixels = set()
    tri2_pixels = set()
    tri3_pixels = set()

    for px in range(min_x1, max_x1, step):
        for py in range(min_y1, max_y1, step):
            if point_in_triangle(px + step/2, py + step/2, tri1):
                tri1_pixels.add((px, py))

    for px in range(min_x2, max_x2, step):
        for py in range(min_y2, max_y2, step):
            if point_in_triangle(px + step/2, py + step/2, tri2):
                tri2_pixels.add((px, py))

    for px in range(min_x3, max_x3, step):
        for py in range(min_y3, max_y3, step):
            if point_in_triangle(px + step/2, py + step/2, tri3):
                tri3_pixels.add((px, py))
    

def draw_pixels():
    canvas.delete("all")  # clear canvas fast

    tri1 = get_triangle_coords(x1, y1, angle1)
    tri2 = get_triangle_coords(x2, y2, angle2)
    tri3 = get_triangle_coords(x3, y3, angle3)

    step = PIXEL_SIZE

    # Precompute triangle pixels
    tri1_pixels = set()
    tri2_pixels = set()
    tri3_pixels = set()

    for px, py in [(x, y) for x in range(int(min(p[0] for p in tri1)), int(max(p[0] for p in tri1)), step)
                            for y in range(int(min(p[1] for p in tri1)), int(max(p[1] for p in tri1)), step)]:
        if point_in_triangle(px + step/2, py + step/2, tri1):
            tri1_pixels.add((px, py))

    for px, py in [(x, y) for x in range(int(min(p[0] for p in tri2)), int(max(p[0] for p in tri2)), step)
                            for y in range(int(min(p[1] for p in tri2)), int(max(p[1] for p in tri2)), step)]:
        if point_in_triangle(px + step/2, py + step/2, tri2):
            tri2_pixels.add((px, py))

    for px, py in [(x, y) for x in range(int(min(p[0] for p in tri3)), int(max(p[0] for p in tri3)), step)
                            for y in range(int(min(p[1] for p in tri3)), int(max(p[1] for p in tri3)), step)]:
        if point_in_triangle(px + step/2, py + step/2, tri3):
            tri3_pixels.add((px, py))

    # Draw pixels
    all_pixels = tri1_pixels | tri2_pixels | tri3_pixels
    for px, py in all_pixels:
        in1 = (px, py) in tri1_pixels
        in2 = (px, py) in tri2_pixels
        in3 = (px, py) in tri3_pixels

        if in1 and in2 and in3:
            color = "white"
        elif in1 and in2:
            color = "yellow"
        elif in1 and in3:
            color = "cyan"
        elif in2 and in3:
            color = "purple"
        elif in1:
            color = "lime"
        elif in2:
            color = "red"
        elif in3:
            color = "blue"

        canvas.create_rectangle(px, py, px+step, py+step, fill=color, outline="")



# ---------- KEY HANDLING ----------
def key_down(event):
    key = event.keysym.lower()
    if key in ["up", "down", "left", "right"]:
        keys2.add(key)
    if key in ["w", "a", "s", "d"]:
        keys1.add(key)
    if key in ["t", "f", "g", "h"]:
        keys3.add(key)

def key_up(event):
    key = event.keysym.lower()
    keys1.discard(key)
    keys2.discard(key)
    keys3.discard(key)

# ---------- MAIN LOOP ----------
def update():
    global x1, y1, x2, y2, x3, y3, angle1, angle2, angle3, last_time
    current_time = time.time()
    dt = current_time - last_time
    last_time = current_time

    # Rotate triangles
    angle1 = (angle1 + ROTATION_SPEED * dt) % 360
    angle2 = (angle2 + ROTATION_SPEED * dt) % 360
    angle3 = (angle3 + ROTATION_SPEED * dt) % 360


    # Move triangles
    if "d" in keys1: x1 += SPEED
    if "a" in keys1: x1 -= SPEED
    if "s" in keys1: y1 += SPEED
    if "w" in keys1: y1 -= SPEED

    if "right" in keys2: x2 += SPEED
    if "left" in keys2: x2 -= SPEED
    if "down" in keys2: y2 += SPEED
    if "up" in keys2: y2 -= SPEED

    if "h" in keys3: x3 += SPEED
    if "f" in keys3: x3 -= SPEED
    if "g" in keys3: y3 += SPEED
    if "t" in keys3: y3 -= SPEED

    draw_pixels()
    window.after(16, update)  # ~60 FPS

# ---------- BIND KEYS ----------
window.bind("<KeyPress>", key_down)
window.bind("<KeyRelease>", key_up)

# ---------- START ----------
update()
window.mainloop()
