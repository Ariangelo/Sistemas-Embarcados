from delphifmx import *
from mainApp import FormPrincipal

def main():
    Application.Initialize()
    Application.Title = 'Andarilho - Robô detector'
    Application.MainForm = FormPrincipal(Application)
    Application.MainForm.Show()
    Application.Run()
    Application.MainForm.Destroy()

if __name__ == '__main__':
    main()
