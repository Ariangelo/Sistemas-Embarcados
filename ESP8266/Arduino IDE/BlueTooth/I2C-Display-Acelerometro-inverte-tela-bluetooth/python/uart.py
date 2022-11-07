from delphifmx import *
from principal import formPrincipal

def main():
    Application.Initialize()
    Application.Title = 'UART (Universal Asynchrounous Receiver/Transmiter)'
    Application.MainForm = formPrincipal(Application)
    Application.MainForm.Show()
    Application.Run()
    Application.MainForm.Destroy()

if __name__ == '__main__':
    main()
