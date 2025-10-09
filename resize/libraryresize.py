import random
import os
from PIL import Image
import string


def resizeimage(file, newsize, choice):
  filename = rename(choice)
  imageinput = Image.open(file)
  imageoutput = imageinput.resize(newsize)
  imageoutput.save(filename)
  print(filename + " saved sucessfully")
  
def namerandom(array):
  randomname = ""
  for i in range(8):
    randomname += random.choice(array)
  return randomname

def rename(choice):
  filename = ""
  if choice == "Y":
    newname = input("enter a name no jpg")
    filename = newname + ".jpg"
  if choice == "N":
    arrayletters = list(string.ascii_lowercase)
    filename = namerandom(arrayletters) + ".jpg"
  return filename
    
def checkfile(file, imageformat):
  checkformat = False
  check = file[-3:]
  if str(check) == imageformat:
    checkformat = True
  return checkformat
  
def readfiletxt(txtfile):
  arraytxt = []
  with open(txtfile, 'r') as filetxt:
    for text in filetxt:
      text = text.strip()
      arraytxt.append(str(text))
    return arraytxt

def directoryimage():
  imagedirectory = "./imagedir"
  listdirectory = os.listdir(imagedirectory)
  return listdirectory
