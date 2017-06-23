{
  Copyright 2017-2017 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Test Generics.Collections unit. }
unit TestGenericsCollections;

interface

uses
  Classes, SysUtils, fpcunit, testutils, testregistry, Generics.Collections;

type
  TTestGenericsCollections = class(TTestCase)
    procedure Test1;
  end;

implementation

type
  TApple = class
    Name: string;
    procedure Eat;
  end;

procedure TApple.Eat;
begin
  // Writeln('TApple.Eat');
end;

type
  TAppleList = specialize TObjectList<TApple>;

procedure TTestGenericsCollections.Test1;
var
  A: TApple;
  Apples: TAppleList;
begin
  Apples := TAppleList.Create(true);
  try
    A := TApple.Create;
    Apples.Add(A);
    Apples.Add(TApple.Create);
    A := TApple.Create;
    Apples.Add(A);

    AssertEquals(3, Apples.Count);
    AssertEquals(2, Apples.IndexOf(A));

    Apples.Delete(0);

    AssertEquals(2, Apples.Count);
    AssertEquals(1, Apples.IndexOf(A));

    Apples.Remove(A);

    AssertEquals(1, Apples.Count);

    Apples.Delete(0);

    AssertEquals(0, Apples.Count);
  finally FreeAndNil(Apples) end;
end;

initialization
  RegisterTest(TTestGenericsCollections);
end.
