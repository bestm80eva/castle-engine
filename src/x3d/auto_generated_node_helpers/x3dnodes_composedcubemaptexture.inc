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
    function GetBack: TAbstractTexture2DNode;
    procedure SetBack(const Value: TAbstractTexture2DNode);
    function GetBottom: TAbstractTexture2DNode;
    procedure SetBottom(const Value: TAbstractTexture2DNode);
    function GetFront: TAbstractTexture2DNode;
    procedure SetFront(const Value: TAbstractTexture2DNode);
    function GetLeft: TAbstractTexture2DNode;
    procedure SetLeft(const Value: TAbstractTexture2DNode);
    function GetRight: TAbstractTexture2DNode;
    procedure SetRight(const Value: TAbstractTexture2DNode);
    function GetTop: TAbstractTexture2DNode;
    procedure SetTop(const Value: TAbstractTexture2DNode);
  public
    property Back: TAbstractTexture2DNode read GetBack write SetBack;
    property Bottom: TAbstractTexture2DNode read GetBottom write SetBottom;
    property Front: TAbstractTexture2DNode read GetFront write SetFront;
    property Left: TAbstractTexture2DNode read GetLeft write SetLeft;
    property Right: TAbstractTexture2DNode read GetRight write SetRight;
    property Top: TAbstractTexture2DNode read GetTop write SetTop;

{$endif read_interface}

{$ifdef read_implementation}

{ TComposedCubeMapTextureNode ----------------------------------------------- }

function TComposedCubeMapTextureNode.GetBack: TAbstractTexture2DNode;
begin
  if FdBack.Value is TAbstractTexture2DNode then
    Result := TAbstractTexture2DNode(FdBack.Value)
  else
    Result := nil;
end;

procedure TComposedCubeMapTextureNode.SetBack(const Value: TAbstractTexture2DNode);
begin
  FdBack.Send(Value);
end;

function TComposedCubeMapTextureNode.GetBottom: TAbstractTexture2DNode;
begin
  if FdBottom.Value is TAbstractTexture2DNode then
    Result := TAbstractTexture2DNode(FdBottom.Value)
  else
    Result := nil;
end;

procedure TComposedCubeMapTextureNode.SetBottom(const Value: TAbstractTexture2DNode);
begin
  FdBottom.Send(Value);
end;

function TComposedCubeMapTextureNode.GetFront: TAbstractTexture2DNode;
begin
  if FdFront.Value is TAbstractTexture2DNode then
    Result := TAbstractTexture2DNode(FdFront.Value)
  else
    Result := nil;
end;

procedure TComposedCubeMapTextureNode.SetFront(const Value: TAbstractTexture2DNode);
begin
  FdFront.Send(Value);
end;

function TComposedCubeMapTextureNode.GetLeft: TAbstractTexture2DNode;
begin
  if FdLeft.Value is TAbstractTexture2DNode then
    Result := TAbstractTexture2DNode(FdLeft.Value)
  else
    Result := nil;
end;

procedure TComposedCubeMapTextureNode.SetLeft(const Value: TAbstractTexture2DNode);
begin
  FdLeft.Send(Value);
end;

function TComposedCubeMapTextureNode.GetRight: TAbstractTexture2DNode;
begin
  if FdRight.Value is TAbstractTexture2DNode then
    Result := TAbstractTexture2DNode(FdRight.Value)
  else
    Result := nil;
end;

procedure TComposedCubeMapTextureNode.SetRight(const Value: TAbstractTexture2DNode);
begin
  FdRight.Send(Value);
end;

function TComposedCubeMapTextureNode.GetTop: TAbstractTexture2DNode;
begin
  if FdTop.Value is TAbstractTexture2DNode then
    Result := TAbstractTexture2DNode(FdTop.Value)
  else
    Result := nil;
end;

procedure TComposedCubeMapTextureNode.SetTop(const Value: TAbstractTexture2DNode);
begin
  FdTop.Send(Value);
end;

{$endif read_implementation}
