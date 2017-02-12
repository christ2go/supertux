import sys
import CppHeaderParser
import os
import pprint
"""
    Generates C++ Code for sqrat binding
"""
class CodeGenerator:
    def __init__(self):
        self.ident = 0
        self.output = ""
        self.vmvar = "v"
        self.varnames = set() # Use set for O(1) query
    def ident(self):
        self.ident += 1
    def deident():
        if self.ident < 1:
            raise "Error"
        self.ident -= 1
    def writeln(self,text):
        self.output += ("\t"*self.ident+text+'\n')
    def emitStmt(self,text):
        self.writeln(text+";")
    def setVmName(self,name):
        self.vmvar = name
    def emitConstant(self,name,value):
        self.writeln("RootTable(%s).Bind(\"%s\",%s)"%(self.vmvar,name,value))
    def addClassVariable(self,varname,classn):
        if varname in self.varnames:
            raise "VariableNameUsed"
        self.varnames.add(varname)
        self.writeln("Class<%s,NoCopy<%s>> %s(%s,\"%s\");"%(classn,classn,varname,self.vmvar,classn))
    def emitFunction(self,funcname,registername):
        self.emitStmt("RootTable(%s).Func(\"%s\",&%s)"%(self.vmvar,registername,funcname))
    def emitSquirrelFunction(self,funcname,registername):
        self.emitStmt("RootTable(%s).SquirrelFunc(\"%s\",&%s)"%(self.vmvar,registername,funcname))
    def emitComment(self,value):
        self.writeln("// %s"%(value))
    def registerClass(self,bindname,varname):
        self.emitStmt("RootTable(%s).Class(\"%s\",&%s)"%(self.vmvar,bindname,varname))
    def addClassMethod(self,varname,classn,function,printCast=False,cast=""):
        if not printCast:
            self.emitStmt("%s.Func(\"%s\",&%s::%s)"%(varname,function,classn,function))
        else:
            self.emitStmt("%s.Func(\"%s\",%s &%s::%s)"%(varname,function,cast,classn,function))
    def addOverloadedMethod(self,varname,classn,function,printCast=False,cast=""):
        if not printCast:
            self.emitStmt("%s.Overload(\"%s\",&%s::%s)"%(varname,function,classn,function))
        else:
            self.emitStmt("%s.Overload(\"%s\",%s &%s::%s)"%(varname,function,cast,classn,function))

    def getOutput(self):
        return self.output

"""
    Generates an appropriate function pointer for a method,
    used when a method is ambigious.
"""
def generateFunctionPointer(method,classN):
    tc = "("
    # first method return type
    if not method["returns"]:
        tc += "void"
    else:
        tc += method["returns"]
    tc += " (%s::*) ("%(classN)
    first = True
    for param in method["parameters"]:
        if not first:
            tc += ","
        tc += param["type"]
        first = False


    tc += ") )"
    return tc

code = """
    /**
     *  This template is used for custom class methods!
     */
    template<typename T, SQInteger (T::*SomeMethod)(HSQUIRRELVM)>
    SQInteger callSquirrelFunc(HSQUIRRELVM vm)
    {
      SQUserPointer data;
      if(SQ_FAILED(sq_getinstanceup(vm, 1, &data, 0)) || !data) {
        sq_throwerror(vm, _SC("Function called without instance!"));
        //return SQ_ERROR;
      }
      auto _this = reinterpret_cast<T*> (data);
      return (_this->*SomeMethod)(vm);

      //return 1;
    }

    void BindSquirrel(HSQUIRRELVM vm) {
            using namespace Sqrat;
"""
import sys
import pprint
funktionen = {}
pp = pprint.PrettyPrinter(indent=4)
generator = CodeGenerator()
klassen = {}
konstanten = {}
for filename in os.listdir("."):
    if not filename.endswith(".hpp"):
        continue
    try:
        cppHeader = CppHeaderParser.CppHeader(filename)
        for Class in cppHeader.classes:
            klassendaten = {
                'Ctor' : None,
                'methods' : [],
                'überladen': {}
            }
            #print(Class)
            cname = Class
            Class = cppHeader.classes[Class]
            überladenC = klassendaten["überladen"] # Counts number of overridden methods
            for method in Class["methods"]["public"]:
                #print(method["name"])
                #pp.pprint(method)
                if(method["returns_pointer"]):
                    continue
                überladenC.setdefault(method["name"],0)
                überladenC[method["name"]] += 1
                if "@scripting" in (method.get("doxygen","")):
                    klassendaten["methods"].append(method)
            if len(klassendaten["methods"]) != 0:
                klassen[cname] = klassendaten
            #pp.pprint(überladenC)
            #pp.pprint([ x["name"] for x in klassendaten["methods"]])
        # Collect functions
        for function in cppHeader.functions:
            #pp.pprint(function)
            if not "@scripting" in (function.get("doxygen","")):
                continue
            funktionen[function["name"]] = function
        # Collect enums
        for enum in cppHeader.enums:
            for value in enum["values"]:
                if "@scripting" in enum.get("doxygen",""):
                    konstanten[value["name"]] = value["value"]
    except CppHeaderParser.CppParseError as e:
        print(e)
        # Generiere Code für Interface und für Funktionen
generator.emitComment("Beginning to declare constant values")
for key in konstanten:
    generator.emitConstant(key,konstanten[key])
generator.emitComment("Declaring functions")
for funktion in funktionen:
    if len(funktionen[funktion]["parameters"]) == 1 and "HSQUIRRELVM" in funktionen[funktion]["parameters"][0]["aliases"]:
        generator.emitSquirrelFunction(funktion,funktion)
    else:
        generator.emitFunction(funktion,funktion)
for klasse in klassen:
    generator.emitComment("Code for Class %s"%(klasse))
    generator.addClassVariable("c_"+klasse,klasse)
    varname = "c_"+klasse
    # Deklariere Variable
    # Keep track of already registered methods (if same name is used twice method needs to be overloaded)
    registered = set()
    for method in klassen[klasse]["methods"]:
        print(method["name"])
        # is this method overridden ? => generate a type thingl
        f = generator.addClassMethod
        if method["name"] in registered:
            f = generator.addOverloadedMethod
        if klassen[klasse]["überladen"][method["name"]] != 1:
            # Generate with type cast
            f(varname,klasse,method["name"],True,generateFunctionPointer(method,klasse))
        else:
            f(varname,klasse,method["name"])
        registered.add(method["name"])
## Generiere Klassen

print(generator.getOutput())
