import sys
import vtk
from vtk.util.vtkImageExportToArray import vtkImageExportToArray
from vtk.util.vtkImageImportFromArray import vtkImageImportFromArray


img1 = sys.argv[1]
img2 = sys.argv[2]

def setupReader(img):
    rd = vtk.vtkPNGReader()
    rd.SetFileName(img1)
    rd.Update()
    imp = vtkImageImportFromArray()
    exp = vtkImageExportToArray()
    exp.SetInputConnection(rd.GetOutputPort())
    imp.SetArray(exp.GetArray())
    return imp


rd1 = setupReader(img1)
rd2 = setupReader(img2)

idiff = vtk.vtkImageDifference()
idiff.SetInputConnection(rd2.GetOutputPort())
idiff.SetImageConnection(rd1.GetOutputPort())
idiff.Update()

err = idiff.GetThresholdedError()

print "Diff:",err

