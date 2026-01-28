from tkinter import *
xval = 0
yval = 0
window = Tk()
window.title("BeanGameAlpha.V0.1")
window.geometry("800x600")
label = Label(window,font=("",50))
label.pack(expand=True)
def key_pressed(event):
    global xval 
    global yval
    if event.keysym.lower() == "right":
        xval += 1
    if event.keysym.lower() == "left":
        xval -= 1
    if event.keysym.lower() == "down":
        yval -= 1
    if event.keysym.lower() == "up":
        yval += 1

def update():
    global xval
    global yval
    label.config(text=f"x: {xval}  y: {yval}")
    window.after(100, update)
window.bind("<Key>", key_pressed)
window.focus_set()
update()

window.mainloop()