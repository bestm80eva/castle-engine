{ -*- buffer-read-only: t -*-

  Copyright 2015-2017 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Automatically generated node properties.

  Do not edit this file manually!
  To add new properties:
  - add them to the text files in nodes_specification/components/ ,
  - and regenerate include files by running
    nodes_specification/x3d-nodes-to-pascal/x3d-nodes-to-pascal.lpr .

  The documentation for properties should go to x3dnodes_documentation.txt . }

{$ifdef read_interface}

  private
    function GetCenter: TVector3Single;
    procedure SetCenter(const Value: TVector3Single);
    function GetNameField: string;
    procedure SetNameField(const Value: string);
    function GetRotation: TVector4Single;
    procedure SetRotation(const Value: TVector4Single);
    function GetScale: TVector3Single;
    procedure SetScale(const Value: TVector3Single);
    function GetScaleOrientation: TVector4Single;
    procedure SetScaleOrientation(const Value: TVector4Single);
    function GetTranslation: TVector3Single;
    procedure SetTranslation(const Value: TVector3Single);
  public
    property Center: TVector3Single read GetCenter write SetCenter;
    property NameField: string read GetNameField write SetNameField;
    property Rotation: TVector4Single read GetRotation write SetRotation;
    property Scale: TVector3Single read GetScale write SetScale;
    property ScaleOrientation: TVector4Single read GetScaleOrientation write SetScaleOrientation;
    property Translation: TVector3Single read GetTranslation write SetTranslation;

{$endif read_interface}

{$ifdef read_implementation}

{ TCADPartNode ----------------------------------------------- }

function TCADPartNode.GetCenter: TVector3Single;
begin
  Result := FdCenter.Value;
end;

procedure TCADPartNode.SetCenter(const Value: TVector3Single);
begin
  FdCenter.Send(Value);
end;

function TCADPartNode.GetNameField: string;
begin
  Result := FdName.Value;
end;

procedure TCADPartNode.SetNameField(const Value: string);
begin
  FdName.Send(Value);
end;

function TCADPartNode.GetRotation: TVector4Single;
begin
  Result := FdRotation.Value;
end;

procedure TCADPartNode.SetRotation(const Value: TVector4Single);
begin
  FdRotation.Send(Value);
end;

function TCADPartNode.GetScale: TVector3Single;
begin
  Result := FdScale.Value;
end;

procedure TCADPartNode.SetScale(const Value: TVector3Single);
begin
  FdScale.Send(Value);
end;

function TCADPartNode.GetScaleOrientation: TVector4Single;
begin
  Result := FdScaleOrientation.Value;
end;

procedure TCADPartNode.SetScaleOrientation(const Value: TVector4Single);
begin
  FdScaleOrientation.Send(Value);
end;

function TCADPartNode.GetTranslation: TVector3Single;
begin
  Result := FdTranslation.Value;
end;

procedure TCADPartNode.SetTranslation(const Value: TVector3Single);
begin
  FdTranslation.Send(Value);
end;

{$endif read_implementation}
