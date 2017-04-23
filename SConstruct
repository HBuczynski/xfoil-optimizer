#!python
# The goal here is to be able to build libs and programs using just
# the list of sources.
# I wish to 'wrap' or 'decorate' the base scons behavior in
# a few ways:
# * default variant builds ('Debug'/'Release')
# * automatic build dirs (which are variant-sensitive)
# - with work-arounds to make *everything* go in the build dir
# * automatic no-fuss globs (that *also* work properly for build dirs)
# * default platform-specific build env vars (also variant-sensitive)
# (i.e. some extra compiler specific CCFLAGS and such)
# * automatic 'installation' of libs, program, and headers into specific
# directories (e.g. '#lib', '#bin', and '#include')
import sys

############################################
# Site-specific setup

# Hmm... this should go somewhere else. SCustomize??
# This is my own site-specific win32 setup...
if sys.platform == 'win32':
    stdinc = [r'c:\usr\include']
    stdlibinc = [r'c:\usr\lib']
else:
    stdinc = []
    stdlibinc = []

############################################
# Generic boiler plate
#-------------------------------------------
import os
import os.path

opts = Options('SCustomize')
opts.Add('debug', 'Build with debugging symbols', 0)
opts.Add('CC', 'Set C compiler')

env = Environment(options=opts)
Help(opts.GenerateHelpText(env))

debug = env.get('debug',0)
build_base = 'build'

if debug:
    env.Append(CPPDEFINES = ['DEBUG', '_DEBUG'])
    variant = 'Debug'
else:
    env.Append(CPPDEFINES = ['NDEBUG'])
    variant = 'Release'

############################################
# PLATFORM SPECIFIC CONFIGS
############################################
#-------------- win32 MSVC -----------------
if env['CC'] == 'cl':
    def freeMSVCHack(env, vclibs):
        # SCons automatically finds full versions of msvc via the registry, so
        # if it can't find 'cl', it may be because we're trying to use the
        # free version
        def isMicrosoftSDKDir(dir):
            return os.path.exists(os.path.join(dir, 'Include', 'Windows.h')) and os.path.exists(os.path.join(dir, 'Lib', 'WinMM.lib'))

        def findMicrosoftSDK():
            import SCons.Platform.win32
            import SCons.Util
            import re
            if not SCons.Util.can_read_reg:
                return None
            HLM = SCons.Util.HKEY_LOCAL_MACHINE
            K = r'Software\Microsoft\.NETFramework\AssemblyFolders\PSDK Assemblies'
            try:
                k = SCons.Util.RegOpenKeyEx(HLM, K)
                p = SCons.Util.RegQueryValueEx(k,'')[0]
                # this should have \include at the end, so chop that off
                p = re.sub(r'(?i)\\+Include\\*$','',p)
                if isMicrosoftSDKDir(p): return p
            except SCons.Util.RegError:
                pass

            K = r'SOFTWARE\Microsoft\MicrosoftSDK\InstalledSDKs'
            try:
                k = SCons.Util.RegOpenKeyEx(HLM, K)
                i=0
                while 1:
                    p = SCons.Util.RegEnumKey(k,i)
                    i+=1
                    subk = SCons.Util.RegOpenKeyEx(k, p)
                    try:
                        p = SCons.Util.RegQueryValueEx(subk,'Install Dir')[0]
                        # trim trailing backslashes
                        p = re.sub(r'\\*$','',p)
                        if isMicrosoftSDKDir(p): return p
                    except SCons.Util.RegError:
                        pass
            except SCons.Util.RegError:
                pass

            return None

        # End of local defs. Actual freeMSVCHack begins here
        if not env['MSVS'].get('VCINSTALLDIR'):
            if os.environ.get('VCToolkitInstallDir'):
                vcdir=os.environ['VCToolkitInstallDir']
                env.PrependENVPath('INCLUDE', os.path.join(vcdir, 'Include'))
                env.PrependENVPath('LIB', os.path.join(vcdir, 'Lib'))
                env.PrependENVPath('PATH', os.path.join(vcdir, 'Bin'))
                env['MSVS']['VERSION'] = '7.1'
                env['MSVS']['VERSIONS'] = ['7.1']
            if not env['MSVS'].get('PLATFORMSDKDIR'):
                sdkdir = findMicrosoftSDK()
                if sdkdir:
                    env.PrependENVPath('INCLUDE', os.path.join(sdkdir, 'Include'))
                    env.PrependENVPath('LIB', os.path.join(sdkdir, 'Lib'))
                    env.PrependENVPath('PATH', os.path.join(sdkdir, 'Bin'))
                    env['MSVS']['PLATFORMSDKDIR']=sdkdir
            # FREE MSVC7 only allows
            # /ML(libc) /MT(libcmt) or /MLd(libcd)
            # Full IDE versions also have
            # /MD(msvcrtd) /MTd(libcmtd) and /MDd(msvcrtd)
            # So if you want to debug with the freever, the only option is
            # the single-threaded lib, /MLd
            vclibs['Debug']='/MTd'
            vclibs['Release']='/MT'

    # MSVC SETUP
    # MDd is for multithreaded debug dll CRT (msvcrtd)
    # MD is for multithreaded dll CRT (msvcrt)
    # These are just my preferences
    vclibs = {'Debug':'/MDd','Release':'/MD'}
    freeMSVCHack(env, vclibs)

    env.Append(CCFLAGS=[vclibs[variant]])
    if debug:
        env.Append(CCFLAGS=Split('/Zi /Fd${TARGET}.pdb'))
        env.Append(LINKFLAGS = ['/DEBUG'])
        # env.Clean('.', '${TARGET}.pdb')
        # Need to clean .pdbs somehow! The above line doesn't work!
    else:
        env.Append(CCFLAGS=Split('/Ot /Ob1 /O2'))

    env.Append(CCFLAGS=Split('/EHsc /J /W3 /Gd'))
    env.Append(LINKFLAGS=['/MACHINE:X64'])
    env.Append(CPPDEFINES=Split('WIN32 _WINDOWS'))

#-------------- gcc-like (default) ---------
else: # generic posix-like
    if debug:
        env.Append(CPPFLAGS = ['-g'])
    else:
        env.Append(CPPFLAGS = ['-O3'])
#-------------------------------------------


# Put all the little .sconsign files into one big file.
# (Does this slow down parallel builds?)
# Need to create the build dir before we put the signatures db in there
fullbuildpath = Dir(build_base).abspath
if not os.path.exists(fullbuildpath): os.makedirs(fullbuildpath)
import dbhash
env.SConsignFile(os.path.join(build_base, 'sconsignatures'), dbhash)


# Make a singleton global object for keeping track of all the extra data
# and methods that are being added
class Globals:
    def __init__(self):
        self.env = env
        self.stdinc = stdinc
        self.stdlibinc = stdlibinc
        self.variant = variant
        self.build_base = os.path.join(build_base, variant)
        self.libname_decorators = { 'Debug' : '_dbg' }
        self.appname_decorators = { 'Debug' : '_dbg' }
        self.incinstdir = '#include'
        self.libinstdir = '#lib'
        self.appinstdir = '#bin'
        self.objcache = {}

    def Glob(self, pat):
        ## GLOB IN THE REAL SOURCE DIRECTORY (NOT BUILD DIR)
        import glob
        prevdir = os.getcwd();
        if pat[0] != '#':
            os.chdir(self.env.Dir('.').srcnode().abspath)
            ret = glob.glob(pat)
        else:
            pat = pat[1:]
            base = os.path.dirname(pat)
            searchdir = self.env.Dir('#').srcnode().abspath
            os.chdir(searchdir)
            ret = ['#'+x for x in glob.glob(pat)]
        os.chdir(prevdir)
        return ret

    def GlobExpand(self, list):
        ## look for pattern-like things and glob on those
        ret = []
        for item in list:
            if item.find('*') or item.find('?') or item.find('['):
                ret += self.Glob(item)
            else:
                ret += [item]
        return ret

    def IsALocalLib(self, lib):
        # This is rather heuristic determining if a lib is local or not
        return lib.find('/') or lib.find(os.sep) or lib[0]=='#'

    def MyHeaderMethod(self, env, source, **dict):
        if type(source)==type(''): source = Split(source)
        source = self.GlobExpand(source)
        nodes = []
        if hasattr(self,'incinstdir') and self.incinstdir:
            for i in source:
                nodes.append( env.Install(self.incinstdir, i) )
        return nodes

    def MyLibraryMethod(self, env, **dict):
        relincs = dict.get('CPPPATH',[])
        dict['CPPPATH'] = ['.'] + relincs + self.stdinc

        # These shenanigans are necessary to get SCons to build non-local
        # sources in the BuildDir instead of their own local directories
        target = dict.pop('target')
        source = dict.pop('source')
        if type(source)==type(''): source = Split(source)
        allsrc = []
        for x in source:
            objbase = os.path.basename(x)
            if self.objcache.get(objbase):
                #print 'Reusing node', objbase
                #NOTE: We should check that defines etc are all the same!!
                allsrc += self.objcache[objbase]
            else:
                onode = env.SharedObject(
                    os.path.splitext(objbase)[0], x,
                    **dict)
                allsrc += onode
                self.objcache[objbase]=onode

        targpath = '#' + os.path.join(self.build_dir, target)
        # decorate libname with e.g. '_dbg'
        if hasattr(self,'libname_decorators'):
            targpath += self.libname_decorators.get(self.variant,'')

        dict['source'] = allsrc
        dict['target'] = targpath
        node = env.Library(**dict)
        if hasattr(self,'libinstdir') and self.libinstdir:
            env.Install(self.libinstdir, node)
        return node

    def MyProgramMethod(self, env, **dict):
        # Enhance CPPPATH,LIBPATH
        dict['CPPPATH'] = ['.'] + dict.get('CPPPATH',[]) + self.stdinc
        dict['LIBPATH'] = dict.get('LIBPATH',[]) + self.stdlibinc

        # These shenanigans are necessary to get SCons to build non-local
        # sources in the BuildDir instead of their own local directories
        target = dict.pop('target')
        source = dict.pop('source',[])
        if type(source)==type(''): source = Split(source)
        allsrc = []
        for x in source:
            objbase = os.path.basename(x)
            if self.objcache.get(objbase):
                print 'Reusing node', objbase
                allsrc += self.objcache[objbase]
            else:
                onode = self.env.SharedObject(
                    os.path.splitext(objbase)[0], x,
                    **dict)
                allsrc += onode
                self.objcache[objbase]=onode

        targpath = '#' + os.path.join(self.build_dir, target)
        # decorate app name with e.g. '_dbg'
        if hasattr(self,'appname_decorators'):
            deco = self.appname_decorators.get(self.variant,'')
            targpath += deco
        # decorate local lib names with e.g. '_dbg'
        if hasattr(self,'libname_decorators'):
            deco = self.libname_decorators.get(self.variant,'')
            # decorate source lib names with e.g. '_dbg'
            LIBS = []
            for l in dict.pop('LIBS',[]):
                if self.IsALocalLib(l):
                    #print "Decorating lib", l, '->', l+deco
                    LIBS += [l+deco]
                else:
                    LIBS += [l]

        dict['target']=targpath
        dict['source']=allsrc
        dict['LIBS']=LIBS
        node = env.Program(**dict)

        if hasattr(self,'appinstdir') and self.appinstdir:
            self.env.Install(self.appinstdir, node)

        return node

    def MySubdirsMethod(self, env, subdirs, **dict):
        # Build sub-directories
        if type(subdirs)==type(''): subdirs=Split(subdirs)
        for d in subdirs:
            savedir = self.build_dir
            self.build_dir = os.path.join(self.build_dir, d)
            env.SConscript(os.path.join(d, 'SConscript'),
                           exports=['G','env'])
            self.build_dir = savedir


G = Globals()

# Wrap the methods of G into method objects, and then add them
# as methods to Environment.
# See http://www.scons.org/cgi-bin/wiki/WrapperFunctions
def MyLibraryMethod(env, **dict):
    G.MyLibraryMethod(env, **dict)
def MyHeaderMethod(env, source, **dict):
    G.MyHeaderMethod(env, source, **dict)
def MyProgramMethod(env, **dict):
    G.MyProgramMethod(env, **dict)
def MySubdirsMethod(env, subdirs, **dict):
    G.MySubdirsMethod(env, subdirs, **dict)
from SCons.Script.SConscript import SConsEnvironment # just do this once
SConsEnvironment.dLibrary = MyLibraryMethod
SConsEnvironment.dProgram = MyProgramMethod
SConsEnvironment.dHeaders = MyHeaderMethod
SConsEnvironment.dSubdirs = MySubdirsMethod

G.build_dir = G.build_base

# Call the SConscript in the top-level directory
env.SConscript('SConscript',build_dir=G.build_dir,exports=['env','G'])