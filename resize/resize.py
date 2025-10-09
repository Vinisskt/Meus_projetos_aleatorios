import sys
import libraryresize

def main():
  if len(sys.argv) != 4:
    print("python namecrypt <image.jpg> or <file.txt> or <directory imagedir> <height> <width> ")
    sys.exit(1)

  newsize = (int(sys.argv[2]),int(sys.argv[3]))
  
  if libraryresize.checkfile(sys.argv[1], "txt") == True:
    arraytxt = libraryresize.readfiletxt(sys.argv[1])
    for txt in arraytxt:
      if libraryresize.checkfile(str(txt), "jpg") == False:
        print("file not in format .jpg")
        sys.exit(1)
      libraryresize.resizeimage(txt, newsize , choice="N")
      
  if libraryresize.checkfile(sys.argv[1], "jpg") == True:
    choice = input("enter Y or N").upper()
    libraryresize.resizeimage(sys.argv[1], newsize, choice)
    
  if libraryresize.checkfile(sys.argv[1], "dir") == True:
    listdirectory = libraryresize.directoryimage()
    for image in listdirectory:
      if libraryresize.checkfile(image, "jpg") == False:
        print("file not in format .jpg")
        sys.exit(1)
      libraryresize.resizeimage("./imagedir/" + image, newsize , choice="N")
  
if __name__ == '__main__':
  main()
