from tkinter import *
SIZE = 7

class Point:
    def __init__(self, x, y, color="black", size=15):
        self.x = x
        self.y = y
        self.color = color
        self.size = size



class GUI:
    def __init__(self):

        self.queue = []
        self.last = None

        self.window = Tk()
        self.window.geometry("500x550")
        self.window.title("Canvas Demo (Faster)")
        self.window.config(bg="gray")
        self.canvas = Canvas(self.window, height=475, width=465)
        self.canvas.place(x=15, y=15)
        self.canvas.bind("<B1-Motion>", self.draw)
        self.canvas.bind("<Button-1>", self.draw_dot)
        self.canvas.bind("<ButtonRelease-1>", self.reset_last)
        self.clear_btn = Button(self.window, text="clear", command=lambda:self.canvas.delete("all"))
        self.clear_btn.place(x=15, y=510)
        self.window.mainloop()

    def reset_last(self, event):
        self.last = None

    def draw_dot(self, event):
        if self.last == None:
            self.canvas.create_line(event.x, event.y, event.x , event.y, width=SIZE, fill = "black", capstyle=ROUND, joinstyle=BEVEL)
            self.last = Point(event.x, event.y)
            
    def draw(self, event):
        print(event.x, event.y)
        #draw on single click
        
        if self.last:
            self.canvas.create_line(self.last.x, self.last.y, event.x, event.y, width= SIZE, fill = "black", capstyle=ROUND, joinstyle=BEVEL)
        self.last = Point(event.x, event.y)
        
g = GUI()

