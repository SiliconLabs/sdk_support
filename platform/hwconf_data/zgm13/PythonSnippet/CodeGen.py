"""
Base support for defining codeGen templates in python. 
"""


import re
import Studio
from PythonSnippet.StudioProject import *
from PythonSnippet.PropertyMap import PropertyMap
import inspect

##Global variables for generation cycle. Initialize just so pydev can do completeion
#: Global context 
CONTEXT   = None
#: Global session
SESSION   = Studio.sourceGen.sourceGenManager.createSourceGenSession()
#: Current location provider 
LOCATION  = SESSION.locationProvider
#: Current device
DEVICE    = None
#: Current model provider
MODEL_PROVIDER = None
#: current sfr page
CUR_SFR_PAGE = None
#: A map of modules and whether they have been generated before.
MODULE_GEN_STATE = {}

#: Map of known template functions key'd by name
__TEMPLATES  = {}

def getProjectName():
    return 

def getContext():
    """
    Returns the current context for debugging. This should NOT be used by production code. 
    If production code requires this then make a new function in CodeGen.py to service the need

    :return: global CONTEXT object
    """
    return CONTEXT

def getModelProvider():
    """
    Returns the current model provider for debugging. This should NOT be used by production code

    :return: global MODEL_PROVIDER object 
    """
    return MODEL_PROVIDER

def addTemplate(name, func):
    """
    Registers a template which can then be called through callMappingGroup
    
    :type  name: string
    :param name: Name of the function so it can be invoked by name
    :type  func: function
    :param name: The function itself 

    """
    global __TEMPLATES
    __TEMPLATES[name] = func

    ## if passed base module name set all instances.     
    #map = getModuleTable()
    #for base, mods in map.items():
    #    if name == base:
    #        for mod in mods:
    #            __TEMPLATES[mod] = func
                
##END: adTemplate()    

ENUM_LITERALS = ["DISABLED", "ENABLED", "ZERO", "ONE"]
IGNORED_TYPES = ['S', 'T', 'elementName', 'argIndex', 'name', 'typedef', 'default', 'initFunc', 'special', 'priority']


def getEnumStr(obj, enum):
    """
    Helper function that returns the names of enums for a property"
    """
    enumStr = None
    for enumName,val in vars(obj).iteritems():
        if not enumName.startswith('__') and enumName not in IGNORED_TYPES:
            if val == enum:
                enumStr = enumName

    if enumStr in ENUM_LITERALS:
        enumStr = str(enum)

    return enumStr


def getPropValueStr(mod, propObj):
    """
    Returns the string name of the current enum setting of the passed property
    """
    prop = mod.ref(propObj.S)
    if propObj.T == PropertyMap.BOOL:
        propValueStr = 'true' if prop.get() else 'false'
    elif propObj.T == PropertyMap.ENUM:
        propValueStr = getEnumStr(propObj, prop.enumIndex)
    else:
        propValueStr = str(prop.get())

    return propValueStr


def setSignalTable(table):
    """
    Placeholder needed by some includes.
    """
    pass

def eval(string):
    """
    Evaluate the string for any codegen style replacements. 
    
    Example "$(myVar) is cool" becomes "josh is cool" if myVar = "josh" 

    :type  string: string
    :param string: string to be evaluated
    :return: The evaluated string
    """
    return CONTEXT.scope.expandText(string, None)

def initSession(context):
    """
    initilize the generation cycle with session and location manager
    
    This MUST be called once and only once at the start of the generation script
    
    """
    global SESSION, LOCATION, DEVICE, CONTEXT, MODEL_PROVIDER
    ## Get session globals
    CONTEXT  = context
    SESSION  = context.session
    LOCATION = context.session.locationProvider
    DEVICE   = context.scope.getValue("object")
    MODEL_PROVIDER = CONTEXT.modelProvider

    ## Set session indent string to default.
    SESSION.indentString = "    "
    return context.scope.findLocation("root")
    
    #return context.session.getRootLocation()

def modeTransitions():
    """
    Provides a list of mode transitions
    
    :return: list of ModeTransition objects
    """
    return [ModeTransition(t) for t in MODEL_PROVIDER.getCollection(DEVICE, 'modeTransitions')]

def scoped(func):
    """
    DECORATOR:
    
    This decorator can be used to give a function it's own scope. This ensures that locations 
    and variables created inside the function are not visible outside the function. 
    """
    def inner(*args, **kwargs):
        pushContext()
        funcReturnValue = func(*args, **kwargs)
        popContext()
        return funcReturnValue
    return inner
##END: scoped decorator
    
def newLocation(parent, path, name=None, owned=False, define=False, packed=False, anchor=None):
    """
    Base for other functiosn. Use new directory, fiel, region instead
    
    :todo: make private
    """
     
    attrs = {
            CONTEXT.ATTR_PARENT  : parent,
            CONTEXT.ATTR_PATH    : path,
            CONTEXT.ATTR_OWNED   : owned,
            CONTEXT.ATTR_DEFINE  : define,
            CONTEXT.ATTR_PACKED  : packed,
            CONTEXT.ATTR_SCOPE   : CONTEXT.scope
            }
    if name  : attrs[CONTEXT.ATTR_NAME]   = name
    if anchor: attrs[CONTEXT.ATTR_ANCHOR] = anchor

    #pushContext(location=parent)
    #attrs[CONTEXT.ATTR_SCOPE] = CONTEXT.scope
    loc = CONTEXT.declareLocation(attrs)
    #popContext()

    return loc
##END:: newLocation

def newDirectory(parent, path, name = None, owned=False, define=False):
    """
    Creates a new Directory location
    
    :type  parent: location
    :param parent: parent location
    :type    path: string
    :param   path: the path for this directory (name of directory)
    :type    name: string
    :param   name: The name of the directory location. If none provided then name = path
    :type   owned: Bool
    :param  owned: If true then the entiry directory will be owned (not recomended)
    :type  define: define
    :param define: If true then the diretory will be defined even if no code is generated into it. 

    :return: the lcoatio object created. This can be used as a parent for other locations
    """
    if name is None: name = path
    return newLocation(parent, "dir({})".format(path), name, owned, define)

def newFile(parent, path, name = None, owned=False, define=False):
    """
    Creates a new File location
    
    :type  parent: location
    :param parent: parent location
    :type    path: string
    :param   path: the path for this file (name of file)
    :type    name: string
    :param   name: The name of the file location. If none provided then name = path with . replaced by _ (hi.c => hi_c)
    :type   owned: Bool
    :param  owned: If true then the entire file will be owned (not recomended)
    :type  define: define
    :param define: If true then the file will be defined even if no code is generated into it. 

    :return: the lcoatio object created. This can be used as a parent for other locations
    """
    if name is None: name = path.replace(".", "_")
    return newLocation(parent, "file({})".format(path), name, owned, define)

def newRegion(parent, path, name = None, owned=False, define=False, packed=False, anchor=None):
    """
    Creates a new Region (location in a file)
    
    :type  parent: location
    :param parent: parent location
    :type    path: string
    :param   path: the path for this location. This will be used for the comment tags if the location is owned
    :type    name: string
    :param   name: The name of the regiion. If none provided then name = path
    :type   owned: Bool
    :param  owned: If true then the region will be owned
    :type  define: define
    :param define: If true then the region will be defined even if no code is generated into it 

    :return: the lcoation object created. This can be used as a parent for other locations
    """
    if name is None: name = path
    return newLocation(parent, "region({})".format(path), name, owned, define, packed, anchor)
        
def newContribution(parent, text="", indent=0, end="\n", defining=False):
    """
    Creates a new contribution
        
    :type    parent: location
    :param   parent: parent location
    :type      text: string
    :param     text: The text of the contribution
    :type    indent: int
    :param   indent: the amount of indention if not default. 
    :type       end: string
    :param      end: string terminator
    :type  defining: bool
    :param defining: If true then this is a defining contribution and will only be ouput when the 
      location is initially defined

    :return: the contributio object. This is typically useless
    """
    if defining:
        c = CONTEXT.addDefiningContribution(parent, text+end)
    else:
        c = CONTEXT.addContribution(parent, text+end)

    c.setIndentDelta(indent)
    return c
##END: newContribution

def newFunction(parent, proto, owned=False, define=True, protoLocation=None):
    """
    Creates a new Function Location
    
    :type  parent: location
    :param parent: parent location
    :type   proto: string
    :param  proto: the function prototype
    :type  define: define
    :param define: If true then the region will be defined even if no code is generated into it 
    :type  protoLocation: location
    :param protoLocation: location wher the prototype should be generated. if not provided no prototype will be generated.

    :return: the lcoation object created. This can be used as a parent for other locations
    """
    ## Parse function prototype
    m = re.match("\s*(\w+)\s+(\S+)\((.*)\)", proto)
    if not m:
        raise Exception("Can't parse prototype {}".format(proto))
    lName   = m.group(2) 

    attrs = {
            CONTEXT.ATTR_NAME        :  lName,
            CONTEXT.ATTR_PARENT      : parent,
            CONTEXT.ATTR_DEFINE      : define,
            CONTEXT.ATTR_SIGNATURE   : proto,
            CONTEXT.ATTR_SCOPE       : CONTEXT.scope}
    if protoLocation:
        attrs[CONTEXT.ATTR_PROTO_LOCATION] = protoLocation
       
    func = CONTEXT.declareFunctionLocation(attrs)
    intLoc = newRegion(func, "body", anchor='body')
    return intLoc
##END: newFunction

def getLocation(name):
    """
    Finds a location by name assuming the location is in scope
    
    :type  name: string
    :param name: name of the location to find
    
    :return: location object or None if no location of that name found
    """
    return CONTEXT.scope.findLocation(name)

def getCurrentLocation():
    """
    Returns the current location. 

    :return: Loaction object pointed to by the 'location' variable
    """
    return CONTEXT.scope.getValue('location')

def getVariable(name):
    """
    retrieves the value of a variable in scope. 
    
    :type  name: string
    :param name: name of variable to get the value for
    
    :return: value of variable. May be various types
    """
    return CONTEXT.scope.getValue(name)

def setVariable(name, value):
    """
    Assign a variable in scope. name = value
    
    :type   name: string
    :param  name: name of variable to set
    :type  value: varies
    :param value: value to set. May be a basic type (string, int) or an object

    """
    return CONTEXT.scope.setValue(name, value)

def newMacro(parent, nameAndParams, expansion):
    """
    Informs loction that a macro is present. 
    
    :type         parent: string
    :param        parent: location that this macro aplies to 
    :type  nameAndParams: string
    :param nameAndParams: what the macro looks like when called
    :type      expansion: string
    :param     expansion: what the macro expands to
    
    """
    parent.setMacro(nameAndParams, expansion)

def pushContext(obj=None, **kwargs):
    """
    Creates a new context frame. This frame is distroyed with popContext(). Locations and varaiables 
    created between pushContext() and popContext() will not be visible after the pop. 
    
    Here we create a context where the current object is myModule and the valu o the variable 
    moduleIndex is 0. After work is done we pop the context so following code will not see that module
    or variable value::
    
        // 'object' currently equals yourModule
        pushContext(myModule, 
                    moduleIndex= 0)
        //do work with myModule and moduleIndex
        popContext()
        //moduleIndex is no longer defince and 'object' is restored to yourModule
    
    
    :type  obj: various
    :param obj: If provide the context's current object is set to this. This is most commonly a module. 
    :type  kwargs: string: various pairs
    :param kwargs: Any key word arguments passed are passed to setValue as (name, value). This is a convience
    function for 
    
    
    
    
    """
    if obj is not None:
        kwargs['object'] = obj
    CONTEXT.pushScope(kwargs)

##END: pushContext

def popContext():
    """
    Pops/removes the most recently pushed context
    """
    CONTEXT.popScope()
##END: popContext

def runTemplate(name, *args):
    """Deperecated: use callMappingGroup"""
    if name in __TEMPLATES:
        print("{}_template()".format(name))
        return __TEMPLATES[name](*args)
    else:
        ##TEMP for modules that need to run origigional mapping group
        print("callMappingGroup({}_template)".format(name))
        return directMappingGroup("{}_generator".format(name))

def mappingGroupExists(name):
    """ 
    Checks if a function is mapped with addTemplate
    
    returns True if so, False if not.
    
    """
    return eval(name.replace('#', "$(moduleNumber)")) in __TEMPLATES

def callMappingGroup(name, *args, **kwargs):
    """
    Calls a function registered with addTemplate
    
    :type  name: string
    :param name: name of function to call
    :type warning: bool
    :param warning: Turns warnings on/off for non-existing functions
    :type  args: various
    :param args: any unnamed args are passed to the function being called
    :type  kwargs: various
    :param kwargs: any key word arguments have assign the value to a varable of the same name as the keword using setVariable().
      the values are see only in the called function. 
    
    """
    if name in __TEMPLATES:
        pushContext(**kwargs)
        __TEMPLATES[name](*args)
        popContext()
    else:
        ##TEMP for modules that need to run origigional mapping group
        print("callMappingGroup({})".format(name))
        directMappingGroup(name, **kwargs)

def directMappingGroup(name, **kwargs):
    """DEPERACATED"""
    CONTEXT.callMappingGroup(name, kwargs)

def genStdConfigFunction(location):
    """Helper that generates a standard configuration function"""
    
    region = newRegion(location, 
                       path = "header",
                       define = True)
    
    newContribution(region, "//" + "=" * 80, defining = True)
    newContribution(region, eval("// $(configFunction)"), defining = True)
    newContribution(region, "//" + "=" * 80, defining = True)
    modeFunc = newFunction(region, 
                           eval("void $(configFunction)(void)"),
                           protoLocation = "configPrototypes",
                           define        = True)
    newContribution(modeFunc, " ")
    return modeFunc


def getPropSetStr(propStruct, propMember, propValueStr):
    '''
    Gets the string to set a property in the form:
        propStruct.propMember = propValueStr;
    '''
    return (propStruct + "." + propMember).ljust(30) + " = " + propValueStr + ";"
##END: getPropSetStr



def getSubClasses(mod):
    """ Yield the classes in module 'mod' """
    for name, obj in inspect.getmembers(mod):
        if hasattr(obj, "__bases__") and hasattr(obj, "priority"):
            #debugPrint("Unssorted {} {}".format(str(obj), obj.priority))
            yield obj  

def getSortedSubClasses(mod):
    for obj in sorted(getSubClasses(mod), key=lambda x: x.priority):
        #debugPrint("Sorted {} {}".format(str(obj), obj.priority))
        yield obj

def genStdProp( prop, func = None, propVal = None, useEnum = False, propName = None, indent = 0):
    '''
    Generates code for a standard property.
        func - setting this will wrap the property in a function call
        propVal - setting this overrides the property's actual value
        useEnum - uses the enum # rather than the enum name as the value
        propName - setting this overrides the name of the property in the code
    '''
    
    ## Ignore properties that do not belong to structures
    if not hasattr(prop, "elementName"):
        return
    
    mod = getVariable('currentModule')
    structName = getVariable('structName')
    libRegion = getCurrentLocation()

    if 'E' in prop.special:
        useEnum = True
    
    if useEnum:
        propVal = str(mod.ref(prop.S).enumIndex)
    elif propVal is None:
        propVal = getPropValueStr(mod, prop)
        
    if hasattr(prop, "wrapFunc"):
        func = prop.wrapFunc
        
    propElem = prop.elementName

    if propName is not None:
        propElem = propName

    if '|' in prop.special:
        if '#' in propElem:
            match = re.search(r'\d+$', mod.name)
            index = match.group() if match else '0'
            propElem = propElem.replace('#', index)
        mask, enum = propVal.rsplit('_',1)
        clearStr = "({} & ~_{}_MASK) | ".format(propElem, mask)
        propVal = clearStr + propVal

    if func is not None:
        propVal = "{}({})".format(func,propVal)

    if structName is not None:
        newContribution(libRegion, getPropSetStr(structName, propElem, propVal), indent = indent)
    elif func is not None:
        newContribution(libRegion, "{};".format(propVal), indent = indent)
    else:
        newContribution(libRegion,"{} = {};".format(propElem, propVal), indent = indent)
##END: genStdProp

def genStdElem(elem):
    '''
    Depricated
    '''
    mod = getVariable('currentModule')
    libRegion = getCurrentLocation()
    elemName = elem.elementName
    
    args = {0:None}
    for prop in getSortedSubClasses(elem):
        
        val = getPropValueStr(mod,prop)
        
        if "~" in prop.special:
            val = "({} & ~{})".format(elemName,val)
        
        if hasattr(prop, 'argIndex'):
            args[prop.argIndex] = val
        else:
            args[0] = val
            
    argString = args[0]
    for i in range(1,len(args)):
        argString += " | {}".format(args[i])
        
    if hasattr(elem, 'description'):
        genStdComment(obj.description)

    elemString = "{} = {};".format(elemName, argString)
    newContribution(libRegion, elemString)
## END genStdElem

def genStdFunc(func):
    """
    Given a function class, this will iterate over all sub classes and construct
    a function call based on the argIndex of each sub-class.
    
    If argIndex doesn't exist, the property will be put into the first argument
    
    If argIndex exists for all properties, but argIndex[0] does not exist,
    the first argument will be the module name (common case)
    """
    
    mod = getVariable('currentModule')
    structName = getVariable('structName')
    libRegion = getCurrentLocation()
    firstProp = True
    
    args = {0:None}
    for prop in getSortedSubClasses(func):
        
        val = getPropValueStr(mod,prop)
        
        if hasattr(prop, 'argIndex'):
            args[prop.argIndex] = val
        else:
            args[0] = val
    
    ## If the first argument doesn't exist, use the module name
    if args[0] is None:
        args[0] = mod.name
    
    argString = args[0]
    for i in range(1,len(args)):
        argString += ", {}".format(args[i])

    propVal = "{}({})".format(func.name, argString)
    
    if hasattr(func, 'description'):
        genStdComment(func.description)
    
    ## If the function is the input to a structure element, construct the appropriate
    ## assignment. Otherwise, just call the function as stand-alone.
    if hasattr(func, "elementName"):
        propElem = func.elementName
        newContribution(libRegion, getPropSetStr(structName, propElem, propVal))
    else:
        newContribution(libRegion, propVal + ';')
## END: genStdFunc

def startGenStdLibCall(typedef, structName, defaultVal, func, text = None):
    '''
    Begins a library call by creating the region to generate code into, and by
    creating and initializing a structure to be passed to the library function.
    Must be followed by a "endGenStdLibCall()"
        typedef: the typedef of the structure
        structName: the name used for the structure variable
        defaultVal: the value that the structure is initialized to
        func: the function that should be called with the structure
        text: the text that precedes the struct's initialization
    
    The structure initialization will follow this form:
    
    text
    typedef structName = defaultVal;
    
    '''
    location = getCurrentLocation()
    pushContext(location=location, structName=structName, func=func)
    if text is not None:
        newContribution(location, text)
    newContribution(location, "{} {} = {};\n".format(typedef, structName, defaultVal))
##END: startGenStdLibCall

def endGenStdLibCall(useDefaultArgs = True, *args):
    '''
    Ends a library call by calling the function designated in startGenStdLibCall()
    with a reference to the library structure.
        moduleName: Setting this overrides the name of the module.
        
    The function call will follow this form:
    
    func(moduleName, &structName);
    
    func and structName are passed into startGenStdLibCall. 
    moduleName is derived from the module's name inside Studio.
    
    '''
    mod = getVariable('currentModule')
    libRegion = getCurrentLocation()
    func = getVariable('func')
    structName = getVariable('structName')

    argList = []
    if useDefaultArgs:
        ## If the mod is an instance, call the setup function with the mod instance
        ## Else, call the setup function with just the init structure
        if mod.name[-1:].isdigit():
            argList.append(mod.name)
        argList.append('&{}'.format(structName))
        
    for arg in args:
        argList.append(arg)
        
    argString = '{}'.format(argList[0])
    for i in range(1,len(argList)):
        argString += ', {}'.format(argList[i])
        
    newContribution(libRegion, "{}({});".format(func, argString))

    popContext()
##END: endGenStdLibCall

def genStdFuncCall(func, *args):
    '''
    Generates a function call in the current location with the format:
    
    func ( moduleName, arg1, arg2, ..., argn);
    
    '''
    location = getCurrentLocation()
    
    argList = []
    for arg in args:
        argList.append(arg)
        
    argString = '{}'.format(argList[0])
    for i in range(1,len(argList)):
        argString += ', {}'.format(argList[i])
    
    funcCallStr = "{}({});".format(func, argString)
    
    newContribution(location,funcCallStr)
##END genStdFuncCall()

def breakStringBySize(str, size, tab = False):
    '''
    Breaks up a string by adding newlines so that each line never
    exceeds 'size'
    '''
    newLine = "\n"
    if tab:
        newLine = newLine + "\t"
    
    if len(str) > size:
        thisLine = str[0:size]
        if '\n' not in thisLine:
            thisLine, restOfStr = thisLine.rsplit(' ', 1)
        else:
            thisLine, restOfStr = thisLine.split('\n',1)
        restOfStr += str[size:]
        str = thisLine + newLine + breakStringBySize(restOfStr, size, tab)
    return str

def commentizeStr(str):
    return "/* " + breakStringBySize(str, 80).replace('\n', '\n * ') + ' */' 

def genNewline():
    location = getCurrentLocation()
    newContribution(location, '')

def genStdComment(str):
    if str != '':
        location = getCurrentLocation()
        str = commentizeStr(str)
        newContribution(location,str)

def genStdMod(mod):
    """
    Iterates over all classes and sub-classes of a module and generates code
    for each structure and function call.
    
    """
    
    print("{}".format(mod.S))
    
    for obj in getSortedSubClasses(mod):
        if str(obj.T) == "struct":
            startRegion(obj.initFunc)
            text = None
            if hasattr(obj, 'description'):
                text = commentizeStr(obj.description) 
            
            startGenStdLibCall(typedef = obj.typedef,
                               structName = obj.name,
                               defaultVal = obj.default,
                               func = obj.initFunc,
                               text = text)
            for subObj in getSortedSubClasses(obj):
                if subObj.T == "func":
                    genStdFunc(subObj) 
                else:
                    genStdProp(subObj) 
            
            endGenStdLibCall()
            endRegion()
        elif obj.T == "func":
            startRegion(obj.name)
            genStdFunc(obj)
            endRegion()
        elif obj.T == "elem":
            startRegion(obj.elementName)
            genStdElem(obj)
            endRegion()
        else: ## regular property
            if hasattr(obj, "elementName"):
                startRegion(obj.name)
                genStdProp(obj)
                endRegion()
                
            

def startRegion(name, configFunc = None, owned = True, define = True):
    '''
    Creates an owned and defined region with the given name, then sets the
    current location to this region
    '''
    
    if configFunc is None:
        configFunc = getCurrentLocation()
    region = newRegion(configFunc, name, owned = owned, define = define)
    pushContext(location=region)
    return region
## END startRegion()
    
def endRegion():
    '''
    Merely pops the current context to remove the current location
    '''
    popContext()
## END endRegion()


def isFirstCall(mod):
    """Determines if the module being called has been generated before"""
    global MODULE_GEN_STATE
    
    if mod in MODULE_GEN_STATE:
        isFirst = MODULE_GEN_STATE[mod]
    else:
        isFirst = True
        
    MODULE_GEN_STATE[mod] = not isFirst

    return isFirst
        
class ModeTransition:
    """
    A class representing a mode transition
    """
    def __init__(self, obj):
        self.obj = obj

    @property
    def sourceModeName(self):
        """Returns source mode name"""
        val = self.obj.previousObject.name
        return val if len(val) else "RESET"
    
    @property
    def destModeName(self):
        """Returns destination mode name"""
        return self.obj.object.name
    
    @property
    def modules(self):
        """Returns a list of module objects in this mode transition"""
        return [Module(x) for x in MODEL_PROVIDER.getCollection(self.obj, 'modules')]
            
    def getModule(self, name):
        """Returns the requested module"""
        for x in MODEL_PROVIDER.getCollection(self.obj, 'modules'):
            if x.object.name == name:
                if "PBCFG" in name: return PortIO(x)
                return Module(x)
            else:
                ## debugPrint("Module \"{}\" not found.".format(name))
                pass
    ##END: getModule

    def pushContext(self, **kwargs):
        """Pushes context with this transition as the current object"""
        kwargs['object'] = self.obj
        pushContext(**kwargs)

    def popContext(self):
        """pops context"""
        popContext()
##END: ModeTransition

class Module:
    """Module object"""
    def __init__(self, obj):
        self.obj = obj
        
    @property
    def isChanged(self):
        """Returns true if any property in this module has changed from src->dest mode"""
        return not MODEL_PROVIDER.objectsEqual(self.obj.previousObject, self.obj.object)
        
    @property
    def name(self):
        """Returns name of the module"""
        return self.obj.object.name
    
    def pushContext(self, **kwargs):
        """pushes context with this moduel as the current object and 'currentModule' set to this module's name"""
        kwargs['object'] = self.obj
        kwargs['currentModule'] = self
        pushContext(**kwargs)

    def popContext(self):
        """pops context"""
        popContext()

    def callMappingGroup(self, name, **kwargs):
        """Calls mapping group with the module as the current object"""
        kwargs['object'] = self.obj
        callMappingGroup(name, **kwargs)
        
    def ref(self, id, skipIfUnchanged=False):
        """Retrieves a propertty reference for the given property id"""
        val = self.obj.object.getPropertyReference(id)
        if skipIfUnchanged and (val.get() == self.prevRef(id).get()):
            return None
        return val
    
    def prevRef(self, id):
        """Returns a property reference for the propety id given. The content of this reference is for the PREVIOUS MODE"""
        return self.obj.previousObject.getPropertyReference(id)
        
    def getPIDs(self):
        """Returns a list of property id's in this module"""
        return self.obj.object.getPropertyIds()

    @property
    def included(self):
        """True if enable check box checked"""
        return self.ref('ABPeripheral.included', False).get()

    def isEnabled(self):
        """Returns whether or not the box is checked"""
        return self.included

    def isPeripheral(self):
        """Returns the ABPeripheral.included property"""
        return bool(self.ref('ABPeripheral.included', skipIfUnchanged=False))

class PortIO(Module):
    """Represens a port IO object"""
    def __init__(self, obj):
        Module.__init__(self, obj)

    @property
    def ports(self):
        """Return a list of ports in this PortIO but NOT in any crossbar"""
        return [Port(x) for x in MODEL_PROVIDER.getCollection(self.obj, 'portBanks')]

    @property
    def included(self):
        return True

class Port(Module):
    """Port object"""
    def __init__(self, obj):
        Module.__init__(self, obj)

    @property
    def included(self):
        return True
    @property
    def pins(self):
        """ Returns a list of poins in this port"""
        return [Port(x) for x in MODEL_PROVIDER.getCollection(self.obj, 'portBanks')]

    def getPin(self, num):
        """Returns the requested pin"""
        for pin in MODEL_PROVIDER.getCollection(self.obj, 'pins'):
            if pin.object.index == num:
                return Pin(pin)
        return None
    ##END: getPin
        

class Pin(Module):
    """A Pin"""
    def __init__(self, obj):
        Module.__init__(self, obj)

    @property
    def included(self):
        return True


