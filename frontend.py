from tkinter import *

class Point:
    def __init__(self, x, y, color="black"):
        self.x = x
        self.y = y
        self.color = color



class GUI:
    def __init__(self):
        #gneral attributes
        self.last = None
        self.points = []
        
        #tkinter stuff
        self.widget_bgc = "black"
        self.widget_fgc = "lawn green"
        self.draw_color = "back"
        self.window = Tk()
        self.window.geometry("500x550")
        self.window.title("Frontend")
        self.window.config(bg=self.widget_bgc)
        self.canvas = Canvas(self.window, height=475, width=465)
        self.canvas.place(x=15, y=15)
        self.canvas.bind("<B1-Motion>", self.draw)
        self.canvas.bind("<Button-1>", self.draw_dot)
        self.canvas.bind("<ButtonRelease-1>", self.reset_last)
        self.clear_btn = Button(self.window, text="clear", command=self.clear_canvas, bg=self.widget_bgc, fg=self.widget_fgc)
        self.clear_btn.place(x=15, y=510)
        self.export_btn = Button(self.window, text="export", command=self.export, bg=self.widget_bgc, fg=self.widget_fgc)
        self.export_btn.place(x=55, y=510)
        self.import_btn = Button(self.window, text="import", command=self.import_, bg=self.widget_bgc, fg=self.widget_fgc)
        self.import_btn.place(x=105, y=510)
        self.size = IntVar()
        self.size.set(7)
        self.slider = Scale(self.window, from_=1, to=20, tickinterval=0, orient=HORIZONTAL, variable=self.size, bg=self.widget_bgc, fg=self.widget_fgc, highlightbackground=self.widget_fgc)
        self.slider.place(x=375, y=505)
        self.window.mainloop()


    def clear_canvas(self):
        self.canvas.delete("all")
        self.points.clear()
        
    def export(self):
        f = open("export.txt", "w")
        result = ""
        for point in self.points:
            if point == "DONE":
                result += "DONE\n"
            else:
                result += str(point[0]) + "|" + str(point[1]) + "\n"
        f.write(result)
        f.close()
        
    def import_(self):
        self.canvas.delete("all")
        f = open("export.txt", "r")
        content = f.readlines()
        f.close()
        last = None
        for i, line in enumerate(content):
            line = line.replace("\n", "")
            if line == "DONE":
                last = None
            else:
                coords = line.split("|")
                x = int(coords[0])
                y = int(coords[1])
                if last:
                    self.canvas.create_line(x, y, last[0] , last[1], width=self.size.get(), fill = "black", capstyle=ROUND, joinstyle=BEVEL)
                if i == len(content) or content[i+1] == "DONE\n":
                    self.canvas.create_line(x, y, x, y, width=self.size.get(), fill = "black", capstyle=ROUND, joinstyle=BEVEL)
                last = (x, y)
            
            
        
    
    def reset_last(self, event):
        self.last = None
        self.points.append("DONE")
        print("PEN UP")

    def draw_dot(self, event):
        print("MOVE TO:", event.x, event.y)
        print("PEN DOWN")
        if self.last == None:
            self.points.append((event.x, event.y))
            self.canvas.create_line(event.x, event.y, event.x , event.y, width=self.size.get(), fill = "black", capstyle=ROUND, joinstyle=BEVEL)
            self.last = Point(event.x, event.y)
            
    def draw(self, event):
        print(event.x, event.y)
        if self.last:
            self.points.append((event.x, event.y))
            self.canvas.create_line(self.last.x, self.last.y, event.x, event.y, width= self.size.get(), fill = self.last.color, capstyle=ROUND, joinstyle=BEVEL)
        self.last = Point(event.x, event.y)
        
g = GUI()

