"""
Various convenience functions for dealing with the Studio project interface
"""

import Studio
import PythonSnippet
import inspect
from PythonSnippet.CodeGen import *

"""
ADDING STUDIO MODULES, EXAMPLE:

This example will add any modules with 'emlib' in their IDs. In this case,
there is only one module that matches - emlib.

projModel = getProjectModel()
addModules(projModel, '.*emlib.*')
updateProjectFromModel(projModel)

"""

"""
CHANGING THE STUDIO PROJECT:

All changes to the project model need to be committed back to Studio with updateProjectFromModel.

For info on the available methods, see https://stash.silabs.com/projects/SIMPLICITY/repos/ide/browse/features/common/scripting-pydev/com.silabs.ide.scripting.python.pydev/lib/_private/project.py
For info on the classes referenced in that file, see https://stash.silabs.com/projects/SIMPLICITY/repos/ide/browse/features/common/scripting-pydev/com.silabs.ide.scripting.python.pydev/lib/_private/StudioClasses.py
"""

def getProject():
    '''
    Gets the project model for the current project
    '''
    projectName = PythonSnippet.CodeGen.getVariable('projectName')
    project = Studio.project.getProject(projectName)
    if project.exists():
        return project
    else:
        print("Project {} does not exist!".format(projectName))
        return None

def getProjectModel():
    '''
    Gets the project model for the current project
    '''
    projectName = PythonSnippet.CodeGen.getVariable('projectName')
    project = Studio.project.getProject(projectName)
    if project.exists():
        return Studio.project.getProjectModel(project)
    else:
        print("Project {} does not exist!".format(projectName))
        return None

def getProjectInfo(project):
    return Studio.project.getProjectInfo(project)

def updateProjectFromModel(projModel):
    '''
    Updates the current project settings using the changes given in projModel

    projModel - a model, gotten from getProjectModel(), that has been modified
               using addModules() or removeModules()

    '''
    Studio.project.updateProjectFromModel(projModel.model.name, projModel, None)

def addModules(projModel, idPattern):
    '''
    Adds modules to the given project model that match the regex idPattern
    '''
    modules = Studio.module.findDescriptorsByUnversionedId(idPattern)

    if modules == []:
        print("Module with pattern {} not found!".format(idPattern))
    modelModified = False
    for module in modules:
        modelModified |= addModule(projModel.model, getUnversionedModuleId(module.id))
    return modelModified

def removeModules(projModel, idPattern):
    '''
    Removes modules from the given project model that match the regex idPattern
    '''
    modules = Studio.module.findEntitiesById(idPattern)
    modelModified = False
    for module in modules:
        modelModified |= removeModule(projModel.model, getUnversionedModuleId(module.id))
    return modelModified

def addModuleExclusion(projModel, theModuleId, excludePattern):
    '''
    Adds a regex pattern to exclude files in this module from the build
    '''
    mod = getModule(projModel, theModuleId)

    if not mod:
        return

    ## Add the exclude pattern
    exclude = Studio.project.projectModelFactory.createMExclusion()
    exclude.setPattern(excludePattern)
    exclude.setBuiltin(True)
    mod.addCustomization(exclude)

def addModuleInclusion(projModel, theModuleId, includePattern):
    '''
    Adds a regex pattern to include files in this module from the build
    '''
    mod = getModule(projModel, theModuleId)

    if not mod:
        return

    ## Add the exclude pattern
    include = Studio.project.projectModelFactory.createMInclusion()
    include.setPattern(includePattern)
    include.setBuiltin(False)
    mod.addCustomization(include)

def removeModuleExclusion(projModel, theModuleId, excludePattern):
    '''
    Removes an exclusion added by addExclusion
    '''
    mod = getModule(projModel, theModuleId)

    if not mod:
        return

    for exclusion in mod.exclusions:
        if exclusion.pattern == excludePattern:
            mod.removeCustomization(exclusion)

def removeModuleInclusion(projModel, theModuleId, includePattern):
    '''
    Removes an inclusion added by addInclusion
    '''
    mod = getModule(projModel, theModuleId)

    if not mod:
        return

    for inclusion in mod.inclusions:
        if inclusion.pattern == includePattern:
            mod.removeCustomization(inclusion)

def dumpModules():
    '''
    Prints out all the modules that are included in the current project.
    '''
    print("Dumping modules in current project:")
    model = getProjectModel()
    for mod in model.model.modules:
        print("\t{}".format(mod.id))
        print('exclusions...')
        for exclusions in mod.exclusions:
            print(exclusions)
        print('inclusions...')
        for inclusions in mod.inclusions:
            print(inclusions)

def getModuleId(pattern):
    modules = Studio.module.findEntitiesById(pattern)
    if len(modules) > 1:
        print("Warning, multiple modules found with this pattern!")
    elif len(modules) == 0:
        print("Warning, module not found!")
        return
    return modules[0].id

def addFileExclusion(projectModel, path):
    exclusion = Studio.project.projectModelFactory.createMExclusion()
    exclusion.setPattern(path)
    projModel = projectModel.getModel()
    projModel.excludedPaths.add(path)

def addIncludePath(projectModel, path, partCompatibility = None):
    '''
    This sets an include path for Studio resources (i.e. to include source files in a certain path in the build)
    This DOES NOT change the include paths of your compiler!
    '''
    includePath = Studio.project.projectModelFactory.createMIncludePath()
    includePath.setUri(path)
    includePath.setLanguageCompatibility('c cpp asm')
    includePath.setPartCompatibility(partCompatibility)
    projModel = projectModel.getModel()
    if includePath not in projModel.getIncludePaths():
        projModel.includePaths.add(includePath)

def addBuildIncludePath(projectModel, path):
    '''
    This sets an include path on all known build configurations of a project
    '''
    path = "{}/{}".format("studio:/project/", path)
    newIncPath = Studio.project.projectModelFactory.createMIncludePath()
    newIncPath.setUri(path)
    newIncPath.setLanguageCompatibility('c cpp asm')
    newIncPath.setUser(True)

    for config in projectModel.getConfigurations():
        included = False
        for includePath in config.getIncludePaths():
            print(includePath)
            if path in includePath.getUri():
                included = True
        if not included:
            config.includePaths.add(newIncPath)

def removeBuildIncludePath(projectModel, path):
    '''
    This removes an include path (if defined) from all known build configurations of a project
    '''
    path = "{}/{}".format("studio:/project/", path)
    for config in projectModel.getConfigurations():
        for includePath in config.getIncludePaths():
            print(includePath)
            if path in includePath.getUri():
                config.includePaths.remove(includePath)


"""
MODULE HELPER FUNCTIONS
"""
def getModule(projModel, theModuleId):
    '''
    Gets the module with the given Id from the model. Returns None if not found
    '''
    model = projModel.model
    theModuleDesc = Studio.module.manager.findCompatibleDescriptor(theModuleId)
    theModuleId = theModuleDesc.unversionedId

    ## Check to see if the model has any modules
    if not model.modules:
        return None

    ## Find the module that matches the given ID
    for mod in model.modules:
        if mod.id == theModuleId:
            break

    if mod.id != theModuleId:
        print("Module not found!")
        return None

    return mod

def getUnversionedModuleId(theModuleId):
    theModuleDesc = Studio.module.manager.findCompatibleDescriptor(theModuleId)
    if theModuleDesc:
        return theModuleDesc.unversionedId
    else:
        return theModuleId

def isModuleInProject(model, id):
    id = getUnversionedModuleId(id)

    for mod in model.modules:
        unversionedId = getUnversionedModuleId(mod.id)
        if unversionedId == id and mod.isBuiltin():
            return True

    return False

def addModule(model, theModuleId):
    theModule = Studio.project.projectModelFactory.createMModule()

    theModuleDesc = Studio.module.manager.findCompatibleDescriptor(theModuleId)
    theModule.setId(theModuleDesc.unversionedId)

    theModule.setBuiltin(True)

    if not isModuleInProject(model, theModule.id):
        print("Adding {} to project!".format(theModuleDesc.label))

        model.modules.add(theModule)
        return True

    return False

def removeModule(model, theModuleId):
    theModuleDesc = Studio.module.manager.findCompatibleDescriptor(theModuleId)
    assert theModuleDesc
    theModuleId = theModuleDesc.unversionedId
    modified = False

    if isModuleInProject(model, theModuleId):
        if model.modules:
            for mod in list(model.modules):
                if mod.id == theModuleId:
                    print("Removing {} from project!".format(theModuleDesc.label))
                    model.modules.remove(mod)
                    #model.modules.add(theModule)
                    modified = True
                    break
        for config in model.configurations:
            if config.modules:
                for mod in list(config.modules):
                    if mod.id == theModuleId:
                        print("Removing {} from {}!".format(theModuleDesc.label, config.label))
                        #model.modules.remove(mod)
                        config.modules.remove(mod)
                        modified = True
                        break
    return modified

def addRemoveLibrary(projModel, modName, libPattern, includes):

    ## If the module is included in any mode, add the library
    ## Else, remove it
    if not projModel:
        return False

    add = False
    for transition in modeTransitions():
        mod = transition.getModule(modName)
        if mod.included:
            add = True

    if add:
        addModules(projModel, libPattern)
        libIncludes = getContext().scope.findLocation('initDevice_c_libinc')
        for include in includes:
            newContribution(libIncludes, '#include "{}"'.format(include))
    else:
        removeModules(projModel, libPattern)

    return add

def addProjectModuleSourceFiles(moduleIdPattern, sourceFiles):
    """
    :param moduleIdPattern: A search pattern to find a module by id (ie 'Emlib')
    :type moduleIdPattern: str
    :param sourceFiles: A list of patterns to add to the inclusion list (ie 'emlib/em_usart.c')
    :type sourceFiles: [str]
    """
    # Create a copy of the project model
    projectModel = getProjectModel()
    model = projectModel.model

    searchModule = None

    # Search for the existing module by id
    for module in model.modules:
        if moduleIdPattern.lower() in module.id:
            searchModule = module
            break

    if searchModule is None:
        return

    includeType = type(Studio.project.projectModelFactory.createMInclusion())

    # Remove all existing source files and exclude from project
    for customization in searchModule.getCustomizations():
        # Only handle MInclusion types
        if type(customization).__name__ in includeType.__name__:
            # Remove source include pattern
            searchModule.removeCustomization(customization)
            # Exclude file from build
            model.excludedPaths.add(customization.pattern)

    # Add current source files to include pattern and un-exclude from project
    for sourceFile in sourceFiles:
        # Add source include pattern
        include = Studio.project.projectModelFactory.createMInclusion()
        include.setPattern(sourceFile)
        searchModule.addCustomization(include)
        # Add file to build
        if include.pattern in model.excludedPaths:
            model.excludedPaths.remove(include.pattern)

    # Update the project model
    updateProjectFromModel(projectModel)

