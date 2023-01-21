MRuby::Gem::Specification.new('mruby-ode') do |spec|
    spec.license = 'BSD-4-Clause'
    spec.author  = 'Jose A. Ramos'
    spec.summary = 'Open Dynamics Engine bindings'

    # spec.version = '0.0.1'
    
    spec.cc.include_paths << "./include"

    # ODE requires threading library, change later if it's a configuration option:
    spec.linker.flags << '-pthread'

    # Install ode separately (for now)
    # See INSTALL.txt at https://bitbucket.org/odedevs/ode/src/master/
    # Make sure to install to use the same floating point values as mruby itself for maximum compatibility.
    spec.linker.libraries << "ode" 

    # Very likely too platform specific, revise later.
    # This is where ODE is installed on Linux
    spec.linker.library_paths << "/usr/local/lib" 
    spec.cc.include_paths << "/usr/local/include"
  end
