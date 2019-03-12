from Tkinter import *
from ttk import Button,Entry
from PIL import Image,ImageTk
root=Tk()
class Main():
    def __init__(self,parent):
        self.parent = parent
        self.parent.title("Login")

        self.page=StringVar()
        self.loginName = StringVar()
        self.loginPass = StringVar()
        self.signinUName = StringVar()
        self.signinPass = StringVar()
        self.signinName = StringVar()
        self.sts = StringVar()
        
        self.createWidgets()
        self.showLogin()
        
    def createWidgets(self):
        Label(self.parent,textvariable = self.page,font=("",20)).pack()
        frame1 = Frame(self.parent)
        Label(frame1,text = "Name").grid(sticky = W)
        Entry(frame1,textvariable = self.loginName).grid(row =0,column =1,pady=10,padx=10)
        Label(frame1,text = "Password").grid(sticky = W)
        Entry(frame1,textvariable = self.loginPass,show="*").grid(row =1,column =1)
        Button(frame1,text="Login",command=self.login).grid(pady=10)
        Button(frame1,text="Sign Up",command=self.signUp).grid(row=2,column=1,pady=10)
        frame1.pack(padx=10,pady=10)
        
        frame2 = Frame(self.parent)
        Label(frame2,text = "Username").grid(sticky = W)
        Entry(frame2,textvariable = self.signinUName).grid(row =0,column =1,pady=10,padx=10)
        Label(frame2,text = "Password").grid(sticky = W)
        Entry(frame2,textvariable = self.signinPass,show="*").grid(row =1,column =1)
        Label(frame2,text = "Name").grid(sticky = W)
        Entry(frame2,textvariable = self.signinName).grid(row =2,column =1,pady=10,padx=10)
        Button(frame2,text="Create",command=self.create).grid(pady=10)
        Button(frame2,text="Back",command=self.showLogin).grid(row=3,column=1,pady=10)
        
        frame3 = Frame(self.parent)
        Label(frame3,text="Loged In",font=("",10)).pack(padx = 10,pady = 10)
        #Button(frame3,text="Log out",command=self.showLogin).grid(row=3,column=1,pady=10)
        #Button(frame3,text="Log Out",command=self.showLogin).grid(row=3,column=1,pady=10)
        
        
        self.loginFrame = frame1
        self.signinFrame = frame2
        self.logedFrame = frame3        
        Label(self.parent,textvariable = self.sts).pack()
        
    def login(self):
        isLoginSuccess = False
        name = self.loginName.get()
        password = self.loginPass.get()
       
        try:
            with open('savedata.txt') as f:
                for line in f:
                    line = line.rstrip('\n')
                    word = line.split(',')
                    if str(name)==word[0] and str(password)==word[1]:
                        print "done loggin"
                        self.showLoged()
                        isLoginSuccess = True
                        self.sts.set("")

                if isLoginSuccess==False:
                    print "fail loggin"
                    self.sts.set("Wrong Name and Password")
        except:
            self.sts.set("Wrong Name and Password")
            
            

    def signUp(self):
        self.page.set("Sign Up")
        self.loginFrame.pack_forget()
        self.signinFrame.pack()
        
    def showLogin(self):
        self.page.set("Login")
        self.signinFrame.pack_forget()
        self.loginFrame.pack()

    def showLoged(self):
        self.page.set("Login by ...")
        self.loginFrame.pack_forget()
        self.logedFrame.pack()
        
    def create(self):
        Uname = self.signinUName.get()
        password = self.signinPass.get()
        name = self.signinName.get()
        f = open("savedata.txt","a+")
        text = ("{0},{1},{2}".format(Uname,password,name))
        f.write(text+'\n')
        f.close()
        self.showLogin()
                                    
if __name__ == "__main__":  
    
    photo = ImageTk.PhotoImage(file='download.jpg')
    labels = Label(root, image=photo)
    labels.pack()
    Main(root)
    root.mainloop()
