// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generators/include/python_CEGUI.h"
#include "NamedArea.pypp.hpp"

namespace bp = boost::python;

void register_NamedArea_class(){

    { //::CEGUI::NamedArea
        typedef bp::class_< CEGUI::NamedArea > NamedArea_exposer_t;
        NamedArea_exposer_t NamedArea_exposer = NamedArea_exposer_t( "NamedArea", bp::init< >() );
        bp::scope NamedArea_scope( NamedArea_exposer );
        NamedArea_exposer.def( bp::init< CEGUI::String const & >(( bp::arg("name") )) );
        bp::implicitly_convertible< CEGUI::String const &, CEGUI::NamedArea >();
        { //::CEGUI::NamedArea::getArea
        
            typedef ::CEGUI::ComponentArea const & ( ::CEGUI::NamedArea::*getArea_function_type )(  ) const;
            
            NamedArea_exposer.def( 
                "getArea"
                , getArea_function_type( &::CEGUI::NamedArea::getArea )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
                    \n\
                        Return the ComponentArea of this NamedArea\n\
            \n\
                    @return\n\
                        ComponentArea object describing the NamedArea's current target area.\n\
                    *\n" );
        
        }
        { //::CEGUI::NamedArea::getName
        
            typedef ::CEGUI::String const & ( ::CEGUI::NamedArea::*getName_function_type )(  ) const;
            
            NamedArea_exposer.def( 
                "getName"
                , getName_function_type( &::CEGUI::NamedArea::getName )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
                    \n\
                        Return the name of this NamedArea.\n\
            \n\
                    @return\n\
                        String object holding the name of this NamedArea.\n\
                    *\n" );
        
        }
        { //::CEGUI::NamedArea::handleFontRenderSizeChange
        
            typedef bool ( ::CEGUI::NamedArea::*handleFontRenderSizeChange_function_type )( ::CEGUI::Window &,::CEGUI::Font const * ) const;
            
            NamedArea_exposer.def( 
                "handleFontRenderSizeChange"
                , handleFontRenderSizeChange_function_type( &::CEGUI::NamedArea::handleFontRenderSizeChange )
                , ( bp::arg("window"), bp::arg("font") )
                , "! perform any processing required due to the given font having changed.\n" );
        
        }
        { //::CEGUI::NamedArea::setArea
        
            typedef void ( ::CEGUI::NamedArea::*setArea_function_type )( ::CEGUI::ComponentArea const & ) ;
            
            NamedArea_exposer.def( 
                "setArea"
                , setArea_function_type( &::CEGUI::NamedArea::setArea )
                , ( bp::arg("area") )
                , "*!\n\
                    \n\
                        Set the Area for this NamedArea.\n\
            \n\
                    @param area\n\
                        ComponentArea object describing a new target area for the NamedArea..\n\
            \n\
                    @return\n\
                        Nothing.\n\
                    *\n" );
        
        }
        { //::CEGUI::NamedArea::setName
        
            typedef void ( ::CEGUI::NamedArea::*setName_function_type )( ::CEGUI::String const & ) ;
            
            NamedArea_exposer.def( 
                "setName"
                , setName_function_type( &::CEGUI::NamedArea::setName )
                , ( bp::arg("name") )
                , "*!\n\
                    \n\
                        set the name for this NamedArea.\n\
            \n\
                    @param area\n\
                        String object holding the name of this NamedArea.\n\
            \n\
                    @return\n\
                        Nothing.\n\
                    *\n" );
        
        }
        { //::CEGUI::NamedArea::writeXMLToStream
        
            typedef void ( ::CEGUI::NamedArea::*writeXMLToStream_function_type )( ::CEGUI::XMLSerializer & ) const;
            
            NamedArea_exposer.def( 
                "writeXMLToStream"
                , writeXMLToStream_function_type( &::CEGUI::NamedArea::writeXMLToStream )
                , ( bp::arg("xml_stream") )
                , "*!\n\
                    \n\
                        Writes an xml representation of this NamedArea to  out_stream.\n\
            \n\
                    @param out_stream\n\
                        Stream where xml data should be output.\n\
            \n\
                    @return\n\
                        Nothing.\n\
                    *\n" );
        
        }
    }

}