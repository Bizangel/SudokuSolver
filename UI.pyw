import tkinter as tk
import subprocess
try:
    import requests
    import urllib3
except:
    messagebox.showinfo('Error','No requests/urllib3 modules found, fetch from internet functionality will NOT work.')
from random import randint
from tkinter import messagebox
    
class Main():
    def __init__(self):
        root = tk.Tk()
        root.geometry('540x580')
        root.title('Sudoku Solver')
        root.iconbitmap('solver_icon.ico')
        root.resizable(False,False)
        root.configure(background='#e9e6e6')
        
        bgcolor = '#d3f6f8'
        
        canvas = tk.Canvas(root,width=540,height=540,bg=bgcolor)
        canvas.place(relx=0,rely=0)
        
        self.Text_Vars = [[],[],[],[],[],[],[],[],[]] #List that will hold all labels object
        self.Entry_Widgets = [[],[],[],[],[],[],[],[],[]] #List that holds entry widgets
        
        #Horizontal Lines
        for i in range(9):
            for j in range(9):
                vcmd = (root.register(self.validatetext),'%d', '%i', '%P', '%s', '%S', '%v', '%V', '%W') 
                Textvar = tk.StringVar()
                temp = tk.Entry(canvas,bg=bgcolor,font=('Arial',30),relief='flat',width=1,validate='key',validatecommand=vcmd,
                             selectborderwidth=10,justify='center',textvariable=Textvar,disabledbackground=bgcolor,
                                disabledforeground='black')
                
                self.Text_Vars[i].append(Textvar) #save text bar
    
                placewidth = 59
                placeheight = 59
                if (i == 2 or i == 5): placeheight-=3
                if (j == 2 or j == 5): placewidth -=3
                
                temp.place(width=placewidth,height=placeheight,x=j*60+1,y=i*60+1)
                self.Entry_Widgets[i].append(temp)
                
                
        for i in range(9):
            if i == 3 or i == 6 or i == 9:
                canvas.create_line((0,60*i),(540,60*i),fill='black',width=6)
            else:
               canvas.create_line((0,60*i),(540,60*i),fill='black')
            
        for i in range(9):
            if i == 3 or i == 6 or i == 9:
                canvas.create_line((60*i,0),(60*i,540),fill='black',width=6)
            else:
                canvas.create_line((60*i,0),(60*i,540),fill='black')
                
                
        #Do menu
        SolveButton = tk.Button(root,text='Solve!',command=self.solve_sudoku)
        SolveButton.place(relx=0.5,rely=1,anchor='s',height=30)
        
        ClearButton = tk.Button(root,text='Clear',command=self.clear_sudoku)
        ClearButton.place(relx=0,rely=1,anchor='sw',height=30)
        
        root.mainloop()
    
    def validatetext(self,d,i,P,s,S,v,V,W):
        try:
            int(S)
            if (S == '0'): return False #Avoid 0's
            if len(P) > 1: return False
            return True
            
        except:
            return False
        
    def solve_sudoku(self):
        sudokustring = ''
        for rowtextvars in self.Text_Vars:
            for textvar in rowtextvars:
                if textvar.get() != '':
                    sudokustring += textvar.get()
                else:
                    sudokustring += '0'
        file = open('sudoku.dat','w')
        file.write(sudokustring)
        file.close()

        try:
            CREATE_NO_WINDOW = 0x08000000
            subprocess.call(['./Solver.exe'],creationflags=CREATE_NO_WINDOW) #Solves sudoku
        except:
            try:
                subprocess.call(['./Solver'],creationflags=CREATE_NO_WINDOW) #try linux alternatives, no exe
            except:#Try with no flags
                try:
                    subprocess.call(['./Solver.exe']) 
                except:
                    try:
                        subprocess.call(['./Solver'])
                    except:
                        messagebox.showinfo('Error','No Solver/Solver.exe found')
                        return

        file = open('solved.dat','r')
        sudokustring = file.read()
        file.close()
        self.read_solved_sudoku(sudokustring)
    def clear_sudoku(self,ignoreConfirm=False):

        if ignoreConfirm: #Delete right away
            for rowentry in self.Entry_Widgets:
                for entry in rowentry:
                    entry.config(state='normal')
                    entry.config(disabledforeground='black')
                    entry.delete(0)
        else:
            if (messagebox.askyesno('Confirmation','Are you sure you want to clear?')):
                for rowentry in self.Entry_Widgets:
                    for entry in rowentry:
                        entry.config(state='normal')
                        entry.config(disabledforeground='black')
                        entry.delete(0)
                    

    def read_sudoku(self,sudokustring):
        '''Reads a sudoku string and places it on board '''
        if sudokustring == 'F':
            messagebox.showinfo('Error','No Solution Found, check your input')
            return
        indexer = 0
        for i in range(9):
            for j in range(9):
                if sudokustring[indexer] != '0':
                    self.Entry_Widgets[i][j].delete(0) #assure is empty
                    self.Entry_Widgets[i][j].insert(0,sudokustring[indexer])
                else: self.Entry_Widgets[i][j].delete(0)
                indexer +=1

    def read_solved_sudoku(self,sudokustring):
        if sudokustring == 'F':
            messagebox.showinfo('Error','No Solution Found, check your input')
            return
        oldstring = ''
        for rowtextvars in self.Text_Vars:
            for textvar in rowtextvars:
                if textvar.get() != '':
                    oldstring += textvar.get()
                else:
                    oldstring += '0'

        indexer = 0
        for i in range(9):
            for j in range(9):
                if oldstring[indexer] == '0': #Means it is new, change colors
                    self.Entry_Widgets[i][j].config(disabledforeground='#1f3e7d')
                self.Entry_Widgets[i][j].delete(0) #assure is empty
                self.Entry_Widgets[i][j].insert(0,sudokustring[indexer])
                self.Entry_Widgets[i][j].config(state='disabled')
                indexer +=1
        
        
        
                



Main()


        
        



        

        
        
        
