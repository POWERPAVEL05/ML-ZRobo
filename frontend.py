from tkinter import *

class Point:
    def __init__(self, x, y, color="black"):
        self.x = x
        self.y = y
        self.color = color



class GUI:
    def __init__(self):
        #gneral attributes
        self.queue = []
        self.last = None

        #tkinter stuff
        self.widget_bgc = "gray"
        self.window = Tk()
        self.window.geometry("500x550")
        self.window.title("Frontend")
        self.window.config(bg=self.widget_bgc)
        self.canvas = Canvas(self.window, height=475, width=465)
        self.canvas.place(x=15, y=15)
        self.canvas.bind("<B1-Motion>", self.draw)
        self.canvas.bind("<Button-1>", self.draw_dot)
        self.canvas.bind("<ButtonRelease-1>", self.reset_last)
        self.clear_btn = Button(self.window, text="clear", command=lambda:self.canvas.delete("all"), bg=self.widget_bgc)
        self.clear_btn.place(x=15, y=510)
        self.size = IntVar()
        self.size.set(7)
        self.slider = Scale(self.window, from_=1, to=20, tickinterval=0, orient=HORIZONTAL, variable=self.size, bg=self.widget_bgc)
        self.slider.place(x=100, y=505)
        self.window.mainloop()

    def reset_last(self, event):
        self.last = None

    def draw_dot(self, event):
        print(event.x, event.y)
        if self.last == None:
            self.canvas.create_line(event.x, event.y, event.x , event.y, width=self.size.get(), fill = "black", capstyle=ROUND, joinstyle=BEVEL)
            self.last = Point(event.x, event.y)
            
    def draw(self, event):
        print(event.x, event.y)
        if self.last:
            self.canvas.create_line(self.last.x, self.last.y, event.x, event.y, width= self.size.get(), fill = self.last.color, capstyle=ROUND, joinstyle=BEVEL)
        self.last = Point(event.x, event.y)
        
g = GUI()

