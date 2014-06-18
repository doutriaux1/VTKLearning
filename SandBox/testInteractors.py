import vtk

renWin = vtk.vtkRenderWindow()


ren = vtk.vtkRenderer()

S=vtk.vtkSphereSource()

m = vtk.vtkPolyDataMapper()

m.SetInputConnection(S.GetOutputPort())

a=vtk.vtkActor()
a.SetMapper(m)

ren.AddActor(a)

renWin.AddRenderer(ren)

class myInteractor(vtk.vtkRenderWindowInteractor):
  def __init__(self,*args,**kargs):

  def ConfigureEvent(self):
    print "Conf event"
  def LeftMouseButtonPressEvent(self,*args):
    print "You pressed left"
i = myInteractor()
i.SetRenderWindow(renWin)

i.Initialize()
renWin.Render()

i.Start()


