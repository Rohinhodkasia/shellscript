import subprocess as sp


def running_command():
    script = sp.run("/home/amantya/Downloads/Temp5/5gCN/build/build_dockers.sh")
    print(script.returncode)
    if int(script.returncode) == 0:
        print("Succesfull")
    else:
        print("failed")

running_command()
