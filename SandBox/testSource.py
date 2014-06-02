import vtk
class vtkSquareSource(vtk.vtkPolyDataAlgorithm):
  def __init__(self):
    self.SetNumberOfInputPorts(0)
    self.ScaleFactor = 1.

  def SetScaleFactor(self,scale):
    self.ScaleFactor=scale

  def RequestData(self,request,inputVector,outputVector):
    print "Request got:",request,inputVector,outputVector
    return vtk.vtkPolyData()


if __name__=="__main__":
  sq = vtkSquareSource()
  pd = sq.GetOutputPort()
  print "PD is:",pd
