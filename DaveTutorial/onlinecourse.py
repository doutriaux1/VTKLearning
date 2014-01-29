#def raw_input(s):
#  print s

#make vtk available to python
import vtk
#ask python what vtk is about
#help(vtk)
#list the things that vtk has
#let's define a function to make that more readable
def list_dir(x):
  for item in dir(x):
     print item

#ask for help about a specific class
#help(vtk.vtkDoubleArray)
#ask what that things parent class allows it to do
#help(vtk.vtkDataArray)

#create an instance of that vtk array class
myArray = vtk.vtkDoubleArray()
#list the things that instance has
#ask specifically how to do something with it
#help(myArray.SetValue)

#lets start to use it
myArray.SetName('my first array')
#give it a size
myArray.SetNumberOfComponents(1)
myArray.SetNumberOfTuples(500*500)
#examine the details of that instance
print(myArray)
#put something in it and inspect it
myArray.SetValue(24, 5.0)
print myArray.GetValue(24)
myArray.SetValue(24, 3.0)
print myArray.GetValue(24)

#lets fill the entire thing
#bring sin() and cos() into pythonA
from math import sin, cos
#run a loop to fill it
for x in range(0,500):
  for y in range(0,500):
     myArray.SetValue(x*500+y, 127.5+(1.0+sin(x/25.0)*cos(y/25.0)))
#now we make a vtk data set to represent some object in space
id = vtk.vtkImageData()
#define geometry
id.SetOrigin(0,0,0)
id.SetSpacing(1,1,1)
#define topology
id.SetDimensions(500,500,1)
#define the point associated data values at those
raw_input("filled array")
print "Ok array size:",myArray.GetSize()
help(id.AllocateScalars)
id.AllocateScalars(id.GetInformation())
#id.AllocateScalars(vtk.VTK_DOUBLE,myArray.GetSize())
raw_input("filled array")
id.GetPointData().SetScalars(myArray)
#examine it
print(id)
raw_input("press enter to continue")
array = id.GetPointData().GetArray('my first array')
print array.GetRange()
raw_input("press enter to continue")

#now we will make a window on our display
renwin = vtk.vtkRenderWindow()
renwin.SetSize(500,500)
renderer = vtk.vtkRenderer()
renwin.AddRenderer(renderer)
renderer.SetBackground2(1,1,1)
renderer.SetGradientBackground(1)
renwin.Render()
raw_input("press enter to continue")

#let's show the data we created in that window
mapper = vtk.vtkDataSetMapper()
mapper.SetInputDataObject(id)
mapper.ScalarVisibilityOff()
actor = vtk.vtkActor()
actor.SetMapper(mapper)
renderer.AddViewProp(actor)
renwin.Render()
raw_input("press enter to continue")
renderer.ResetCamera()
renwin.Render()
raw_input("press enter to continue to see data")

#let's change how it looks
context = actor.GetProperty()
context.SetDiffuseColor(0,1,1)
renwin.Render()
raw_input("press enter to continue")

#lets inspect the topology
context.SetRepresentationToWireframe()
renwin.Render()
raw_input("press enter to continue")
renderer.GetActiveCamera().Zoom(10)
renwin.Render()
raw_input("press enter to continue")

#reset how it looks
context.SetRepresentationToSurface()
renderer.ResetCamera()

#lets inspect the data values
mapper.ScalarVisibilityOn()
renwin.Render()
raw_input("press enter to continue")

#we need to match up the lookup table and data ranges
myArray.GetRange()
mapper.SetScalarRange(127,129)
renwin.Render()
raw_input("press enter to continue")

#lets read some data
#create a reader that reads a file and creates a vtk data structure
reader = vtk.vtkDataSetReader()
#filename = raw_input("Where is the SaintHelens.vtk file? ")
filename = "SaintHelens.vtk"
reader.SetFileName(filename)
reader.Update()
id = reader.GetOutput()
print(id.GetClassName())
print(id.GetBounds())
print id.GetPointData().GetArray(0).GetRange()
raw_input("press enter to continue")

#lets show it
mapper.SetInputConnection(reader.GetOutputPort())
mapper.SetScalarRange(682.0, 2543.0)
actor.VisibilityOn()
renwin.Render()
renderer.ResetCamera()
renwin.Render()
raw_input("press enter to continue")

#not we make a filter to free up the constraints on thegeometry 
triangles = vtk.vtkDataSetTriangleFilter()
triangles.SetInputConnection(reader.GetOutputPort())
triangles.Update()
print(triangles.GetOutput().GetClassName())
print(triangles.GetOutput().GetBounds())
raw_input("press enter to continue")

#now we bend the geometry according to the data value
warp = vtk.vtkWarpScalar()
list_dir(warp)
raw_input("press enter to continue")
warp.SetInputConnection(triangles.GetOutputPort())
warp.Update()
print(warp.GetOutput().GetBounds())
raw_input("press enter to continue after bounds")

#now lets show it
mapper.SetInputConnection(warp.GetOutputPort())
renwin.Render()
renderer.ResetCamera()
renwin.Render()
raw_input("press enter to continue after render")

#lets remove the low lying data
cf = vtk.vtkClipDataSet()
mapper.SetInputConnection(cf.GetOutputPort())
cf.SetInputConnection(warp.GetOutputPort())
plane = vtk.vtkPlane()
cf.SetClipFunction(plane)
print plane
print warp.GetOutput().GetBounds()
plane.SetOrigin(560000,5120000,2000)
cf.Update()
print cf.GetOutput().GetBounds()
renwin.Render()
raw_input("press enter to continuei after clip")

#now we want to interact with the data so we listen to UI events
iren = vtk.vtkRenderWindowInteractor()
renwin.SetInteractor(iren)

#now lets make a widget that moves a shape in the scene when the mouse moves
widget = vtk.vtkImplicitPlaneWidget()
widget.PlaceWidget(warp.GetOutput().GetBounds())
widget.SetOrigin([plane.GetOrigin()[x] for x in 0,1,2])
widget.SetNormal([plane.GetNormal()[x] for x in 0,1,2])
widget.SetInteractor(iren)

#and we'll connect it to our clipping filter
def cb(obj,event):
     global plane
     obj.GetPlane(plane)
widget.AddObserver("InteractionEvent", cb)
widget.SetEnabled(1)
widget.DrawPlaneOn()
widget.TubingOn()
renwin.Render()
raw_input("press enter to continuei after ineteractor")

#now we start the UI loop
#iren.Initialize()
raw_input("intialied")
renwin.Render()
raw_input("render")
iren.Start()
raw_input("press enter to quit")

