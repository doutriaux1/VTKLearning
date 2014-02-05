import sys
#sys.path.insert(0,"/git/HyperwallDataBrowse/HCI_Browser")
#import NcImageDataReader as NcR
import vtk
from vtk.util import numpy_support as VN

import numpy

import cdms2

f=cdms2.open(sys.prefix+"/sample_data/clt.nc")
s=f("clt",slice(0,1),slice(20,22),slice(20,22),squeeze=1)
print s

m=s.getGrid().getMesh()
print m

m2 = numpy.ascontiguousarray(numpy.transpose(m,(0,2,1)))
print m2
m2.resize((m2.shape[0]*m2.shape[1],m2.shape[2]))

print m2.shape
print m2
m3=numpy.concatenate((m2,numpy.zeros((m2.shape[0],1))),axis=1)
ug = vtk.vtkUnstructuredGrid()
pts = vtk.vtkPoints()
ppV = VN.numpy_to_vtk(m3,deep=True)
data = VN.numpy_to_vtk(s.filled(),deep=True)
indices=numpy.arange(m2.shape[0],dtype=numpy.int64)
pts.SetData(ppV)
ug.SetPoints(pts)
indices.resize((m2.shape[0]/4,4))
print indices
cellArray = VN.numpy_to_vtkIdTypeArray(indices,deep=True)
#ug.SetCells(vtk.VTK_TETRA,cellArray)
# Gives error:
#Traceback (most recent call last):
#    File "read_clt.py", line 35, in <module>
#        ug.SetCells(vtk.VTK_TETRA,cellArray)
#        TypeError: arguments do not match any overloaded methods

for i in range(4):
  lst = vtk.vtkIdList()
  for j in range(4):
    lst.InsertNextId(i*4+j)

  #cellArray = VN.numpy_to_vtkIdTypeArray(numpy.array(index,dtype=numpy.int64))
  ug.InsertNextCell(vtk.VTK_TETRA,lst)
  # Gives error:
  #Traceback (most recent call last):
  #    File "read_clt.py", line 39, in <module>
  #        ug.InsertNextCell(vtk.VTK_TETRA,cellArray)
  #TypeError: InsertNextCell argument 2: method requires a vtkIdList, a vtkIdTypeArray was provided.


