#include "Cat.h"
#include <cstring>

Cat::Cat()
  : mSound(0),
    mColor(0),
    mWhiskerLength(0)
{
  // empty
}

Cat::Cat(const char *sound_in, const char *color_in, double whisker_length)
  : mSound(0),
    mColor(0),
    mWhiskerLength(whisker_length)
{
  setSound(sound_in);
  setColor(color_in);
}

Cat::Cat(const Cat &src)
  : mSound(0),
    mColor(0),
    mWhiskerLength(0)
{
  *this = src;
}

Cat::~Cat()
{
  deleteSound();
  deleteColor();
}

Cat &Cat::operator=(const Cat &rhs)
{
  setSound(rhs.mSound);
  setColor(rhs.mColor);
  setWhiskerLength(rhs.mWhiskerLength);
  return *this;
}

void Cat::setSound(const char *sound_in)
{
  deleteSound();
  if(sound_in)
    {
      mSound = new char[std::strlen(sound_in) + 1];
      std::strcpy(mSound, sound_in);
    }
}

void Cat::setColor(const char *color_in)
{
  deleteColor();
  if(color_in)
    {
      mColor = new char[std::strlen(color_in) + 1];
      std::strcpy(mColor, color_in);
    }
}

void Cat::setWhiskerLength(double whisker_length)
{
  mWhiskerLength = whisker_length;
}

const char * Cat::speak() const
{
  return mSound;
}

const char * Cat::color() const
{
  return mColor;
}

double Cat::getWhiskerLength() const
{
  return mWhiskerLength;
}

void Cat::deleteSound()
{
  if(mSound)
    {
      delete [] mSound;
      mSound = 0;
    }
}

void Cat::deleteColor()
{
  if(mColor)
    {
      delete [] mColor;
      mColor = 0;
    }
}

#include <iostream>
#include "Cat.h"
#include "Dog.h"

int main()
{
  Cat cat1("Meow", "Tabby", 5.);
  Cat cat2("Meow", "Siamese", 3.4);
  Dog dog1("Bark", "Brown", 10);
  Dog dog2("Bark", "Red", 8);

  std::cout << "Before Set" << std::endl;
  std::cout << "Cat1: " << cat1.speak() << " "
            << cat1.color() << " "
            << cat1.getWhiskerLength() << std::endl;
  std::cout << "Cat2: " << cat2.speak() << " "
            << cat2.color() << " "
            << cat2.getWhiskerLength() << std::endl;
  std::cout << "Dog1: " << dog1.speak() << " "
            << dog1.color() << " "
            << dog1.getFriendliness() << std::endl;
  std::cout << "Dog2: " << dog2.speak() << " "
            << dog2.color() << " "
            << dog2.getFriendliness() << std::endl;

  cat1.setSound("Mew");
  cat1.setWhiskerLength(5.4);
  cat2.setColor("Black");
  cat2.setWhiskerLength(3.9);
  dog1.setColor("Yellow");
  dog1.setFriendliness(7);
  dog2.setSound("Woof");
  dog1.setFriendliness(10);
  
  std::cout << std::endl;
  std::cout << "After Set" << std::endl;
  std::cout << "Cat1: " << cat1.speak() << " "
            << cat1.color() << " "
            << cat1.getWhiskerLength() << std::endl;
  std::cout << "Cat2: " << cat2.speak() << " "
            << cat2.color() << " "
            << cat2.getWhiskerLength() << std::endl;
  std::cout << "Dog1: " << dog1.speak() << " "
            << dog1.color() << " "
            << dog1.getFriendliness() << std::endl;
  std::cout << "Dog2: " << dog2.speak() << " "
            << dog2.color() << " "
            << dog2.getFriendliness() << std::endl;

  return 0;
}

#include "Dog.h"
#include <cstring>

Dog::Dog()
  : mSound(0),
    mColor(0),
    mFriendliness(10)
{
  // empty
}

Dog::Dog(const char *sound_in, const char *color_in, int friendliness)
  : mSound(0),
    mColor(0),
    mFriendliness(friendliness)
{
  setSound(sound_in);
  setColor(color_in);
}

Dog::Dog(const Dog &src)
  : mSound(0),
    mColor(0),
    mFriendliness(10)
{
  *this = src;
}

Dog::~Dog()
{
  deleteSound();
  deleteColor();
}

Dog &Dog::operator=(const Dog &rhs)
{
  setSound(rhs.mSound);
  setColor(rhs.mColor);
  setFriendliness(rhs.mFriendliness);
  return *this;
}

void Dog::setSound(const char *sound_in)
{
  deleteSound();
  if(sound_in)
    {
      mSound = new char[std::strlen(sound_in) + 1];
      std::strcpy(mSound, sound_in);
    }
}

void Dog::setColor(const char *color_in)
{
  deleteColor();
  if(color_in)
    {
      mColor = new char[std::strlen(color_in) + 1];
      std::strcpy(mColor, color_in);
    }
}

void Dog::setFriendliness(int friendliness)
{
  if(friendliness >= 0 && friendliness <= 10)
    {
      mFriendliness = friendliness;
    }
}
  
const char * Dog::speak() const
{
  return mSound;
}

const char * Dog::color() const
{
  return mColor;
}

int Dog::getFriendliness() const
{
  return mFriendliness;
}

void Dog::deleteSound()
{
  if(mSound)
    {
      delete [] mSound;
      mSound = 0;
    }
}

void Dog::deleteColor()
{
  if(mColor)
    {
      delete [] mColor;
      mColor = 0;
    }
}

#include "Name.h"
#include <cstring>

Name::Name()
{
  mName[0] = 0;
}

const char *Name::getName() const
{
  return mName;
}

void Name::setName(const char *name)
{
  if(std::strlen(name) < BUF_SIZE)
    {
      std::strcpy(mName, name);
    }
  else
    {
      std::strncpy(mName, name, BUF_SIZE - 1);
      mName[BUF_SIZE-1] = 0;
    }
}

#include <fstream>
#include <iostream>

#include "Name.h"

void read_file()
{
  char line[BUF_SIZE];
  std::ifstream fin("students.txt");

  while(fin.getline(line, BUF_SIZE))
    {
      std::cout << "read: " << line << std::endl;
    }
  
  fin.close();
}


int main(int argc, char *argv[])
{
  read_file();
  return 0;
}

#include <cstring>
#include "DTrack.h"

// Default constructor, sets pointers to 0.
DTrack::DTrack()
  : mLength(0), mTitle(0)
{
  // empty
}

// Normal constructor, sets pointers to 0.
// This allows the SetTitle method to work correctly
DTrack::DTrack(const int length_in, const char *title_in)
  : mLength(0), mTitle(0)
{
  this->SetLength(length_in);
  this->SetTitle(title_in);
}

// Copy constructor, sets pointers to 0.
// Allows assignment operator to use SetTitle.
DTrack::DTrack(const DTrack &src)
  : mLength(0), mTitle(0)
{
  *this = src;
}

// Destructor, deallocates the memory, if accessed.
DTrack::~DTrack()
{
  if(this->mTitle)
    {
      delete [] this->mTitle;
      this->mTitle = 0;
    }
}

// Assignment operator uses Set methods to centralize
// the memory management work.
DTrack &DTrack::operator=(const DTrack &rhs)
{
  this->SetLength(rhs.mLength);
  this->SetTitle(rhs.mTitle);
  return *this;
}

/* DTrack objects will be ordered by
 * the ASCII value of the titles.  If
 * 2 objects have the same title, then the
 * length of the tracks will be used to order
 * them. */
bool DTrack::operator==(const DTrack &rhs) const
{
  /* title comparison first */
  if(this->mTitle && rhs.mTitle)
    { // both have contents
      int order = std::strcmp(this->mTitle, rhs.mTitle);
      if(order != 0)
        { // contents don't match
          return false;
        }
    }
  else if(this->mTitle || rhs.mTitle)
    { // only 1 has contents
      return false;
    }
  /* at this point either neither title has contents,
   * or both have same contents */
  
  /* length comparison only if titles are same */
  return this->mLength == rhs.mLength;
}

bool DTrack::operator!=(const DTrack &rhs) const
{
  return !(*this == rhs);
}

bool DTrack::operator<(const DTrack &rhs) const
{
  /* title comparison first */
  if(this->mTitle && rhs.mTitle)
    { // both have contents
      int order = std::strcmp(this->mTitle, rhs.mTitle);
      if(order < 0)
        { // lhs is less than rhs by title
          return true;
        }
      else if(order > 0)
        { // lhs is greater than rhs by title
          return false;
        }
      else
        { // titles are same
          // empty
        }
    }
  else if(this->mTitle)
    { // lhs has title, rhs has none.
      return false;
    }
  else if(rhs.mTitle)
    { // lhs has no title, rhs has one.
      return true;
    }
  /* at this point either neither title has contents,
   * or both have same contents */
  
  /* length comparison only if titles are same */
  return this->mLength < rhs.mLength;
}

bool DTrack::operator<=(const DTrack &rhs) const
{
  return *this == rhs || *this < rhs;
}

bool DTrack::operator>(const DTrack &rhs) const
{
  return rhs < *this;
}

bool DTrack::operator>=(const DTrack &rhs) const
{
  return *this == rhs || rhs < *this;
}

int DTrack::GetLength() const
{
  return this->mLength;
}

bool DTrack::SetLength(const int length_in)
{
  if(length_in >= 0)
    {
      this->mLength = length_in;
      return true;
    }
  return false;
}

// const char * ensures that code outside the
// class will not corrupt our data, or overwrite
// the end of our allocated memory.
const char * DTrack::GetTitle() const
{
  return this->mTitle;
}

// This method enforces the assumption that
// mTitle will be 0 if it does not point at
// valid heap memory.  Any other value in
// mTitle means it points to valid heap memory.
bool DTrack::SetTitle(const char *title_in)
{
  // release existing memory
  if( this->mTitle )
    {
      delete [] this->mTitle;
      this->mTitle = 0;
    }
  
  // allocate just enough new memory
  this->mTitle = new char [std::strlen(title_in)+1];
  
  // if memory was allocated, copy the data
  if(this->mTitle)
    {
      std::strcpy(this->mTitle, title_in);
      return true;
    }
  else
    {
      return false;
    }
}

std::ostream & operator<<(std::ostream &os, const DTrack &rhs)
{
  // protect against title-less DTracks.
  const char *title = rhs.GetTitle();
  if(title == 0) { title = ""; }
  os << rhs.GetLength() << " " << title;
  return os;
}

// Unfortunately, the input operator doesn't know how
// big the biggest string really is.  It tries to guess,
// but memory corruption could occur in this function
// if a very long title is used.
std::istream & operator>>(std::istream &is, DTrack &rhs)
{
  int  length;
  char *title = new char[MAX_TITLE_LENGTH];
  is >> length >> title;
  if(is)
    {
      rhs.SetLength(length);
      rhs.SetTitle(title);
    }
  delete [] title;
  title = 0;
  return is;
}

#include <iostream>
#include <fstream>
#include "DTrack.h"

int main(int argc, char **argv)
{
  std::ifstream fin("song_list.txt");
  DTrack t;
  
  while(fin)
    {
      fin >> t;
      if(fin)
        {
          std::cout << t << std::endl;
        }
    }
  
  return 0;
}

#include "Atom.h"

Atom::Atom()
  : m_number(0)
{
  // empty
}

Atom::Atom(int number)
  : m_number(number)
{
  // empty
}

int Atom::getNumber() const
{
  return m_number;
}

Atom &Atom::operator=(const Atom &rhs)
{
  m_number = rhs.m_number;
  return *this;
}

Atom Atom::operator+(const Atom &rhs) const
{
  int new_number = m_number + rhs.m_number;
  Atom new_atom(new_number);
  return new_atom;
}

Atom &Atom::operator+=(const Atom &rhs)
{
  m_number += rhs.m_number;
  return *this;
}

bool Atom::operator==(const Atom &rhs) const
{
  return m_number == rhs.m_number;
}

bool Atom::operator<(const Atom &rhs) const
{
  return m_number < rhs.m_number;
}

Atom::operator bool() const
{
  return m_number != 0;
}


std::ostream &operator<<(std::ostream &lhs, const Atom &rhs)
{
  lhs << "Atomic Number: " << rhs.getNumber();
  return lhs;
}

std::istream &operator>>(std::istream &lhs, Atom &rhs)
{
  std::string s;
  int n = 0;
  lhs >> s >> s >> n;
  if(lhs)
    {
      Atom tmp(n);
      rhs = tmp;
    }
  return lhs;
}

#include "Complex.h"

Complex::Complex()
  : mReal(0.0), mImg(0.0)
{
  // empty
}

Complex::Complex(const double r, const double i)
  : mReal(r), mImg(i)
{
  // empty
}

double Complex::getReal() const
{
  return mReal;
}

double Complex::getImg() const
{
  return mImg;
}

Complex Complex::operator-(const Complex &rhs) const
{
  Complex result(mReal - rhs.mReal,
                 mImg - rhs.mImg);
  return result;
}

Complex Complex::operator*(const double &rhs) const
{
  Complex result(mReal * rhs,
                 mImg * rhs);
  return result;
}


Complex operator+(const Complex &lhs, const Complex &rhs)
{
  Complex result(lhs.getReal() + rhs.getReal(),
                 lhs.getImg() + rhs.getImg());
  return result;
}

Complex operator*(const double &lhs, const Complex &rhs)
{
  return rhs * lhs;
}

std::ostream &operator<<(std::ostream &os, const Complex &c)
{
  os << c.getReal() << " + " << c.getImg() << "i";
  return os;
}