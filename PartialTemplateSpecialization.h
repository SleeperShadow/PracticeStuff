#pragma once

class MyController {};

template <class Arg> class Button {};

template <class Window, class Controller>
class Widget
{

};

template<class Window>
class Widget<Window, MyController>
{

};

template <class ButtonArg>
class Widget<Button<ButtonArg>, MyController>
{

};