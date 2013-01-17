{
  Copyright 2007-2013 Michalis Kamburelis.

  This file is part of "Castle Game Engine".

  "Castle Game Engine" is free software; see the file COPYING.txt,
  included in this distribution, for details about the copyright.

  "Castle Game Engine" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

  ----------------------------------------------------------------------------
}

{ Material and texture properties from external files (TMaterialProperty,
  global MaterialProperties collection). }
unit CastleMaterialProperties;

interface

uses CastleUtils, CastleClassUtils, Classes, DOM, CastleSoundEngine, FGL;

type
  { Store information that is naturally associated with a given material
    or texture in an external file. Right now this allows to define things
    like footsteps, toxic ground (hurts player), and bump mapping.

    In the future, it should be possible to express all these properties
    in pure VRML/X3D (inside Appearance / Material / ImageTexture nodes).
    Right now, you can do this with bump mapping, see
    http://castle-engine.sourceforge.net/x3d_extensions.php#section_ext_bump_mapping ,
    but not footsteps or toxic ground.
    In the future it should also be possible to express these properties
    in 3D authoring software (like Blender), and easily export them
    to appropriate VRML/X3D nodes.
    For now, this TMaterialProperty allows us to easily customize materials
    in a way that is not possible in Blender.

    Using an external file for material properties has also long-term
    advantages: it can be shared across many 3D models, for example
    you can define footsteps sound for all grounds using the @code(grass.png)
    textures, in all levels, at once.

    You have to load an XML file by setting
    @link(TMaterialProperties.FileName MaterialProperties.FileName) property. }
  TMaterialProperty = class
  private
    FTextureBaseName: string;
    FFootstepsSound: TSoundType;
    FToxic: boolean;
    FToxicDamageConst, FToxicDamageRandom, FToxicDamageTime: Single;
    FNormalMap: string;
    procedure LoadFromDOMElement(Element: TDOMElement; const BaseUrl: string);
  public
    { Texture basename to associate this property will all appearances
      using given texture. For now, this is the only way to associate
      property, but more are possible in the future (like MaterialNodeName). }
    property TextureBaseName: string read FTextureBaseName;

    { Footsteps sound to make when player is walking on this material.
      stNone is no information is available. }
    property FootstepsSound: TSoundType read FFootstepsSound;

    { Is the floor toxic when walking on it.
      @groupBegin }
    property Toxic: boolean read FToxic;
    property ToxicDamageConst: Single read FToxicDamageConst;
    property ToxicDamageRandom: Single read FToxicDamageRandom;
    property ToxicDamageTime: Single read FToxicDamageTime;
    { @groupEnd }

    { Normal map texture URL. This is a simple method to activate bump mapping,
      equivalent to using normalMap field in an Appearance node of VRML/X3D, see
      http://castle-engine.sourceforge.net/x3d_extensions.php#section_ext_bump_mapping .

      In case both VRML/X3D Appearance specifies normalMap and we have
      NormalMap defined here, the VRML/X3D Appearance is used. }
    property NormalMap: string read FNormalMap;
  end;

  { Material properties collection, see TMaterialProperty. }
  TMaterialProperties = class(specialize TFPGObjectList<TMaterialProperty>)
  private
    FFileName: string;
    procedure SetFileName(const Value: string);
  public
    { Load material properties from given XML file.
      See Castle1 and fps_game data for examples how this looks like,
      in @code(material_properties.xml). }
    property FileName: string read FFileName write SetFileName;

    { Find material properties for given texture basename.
      Returns @nil if no material properties are found
      (in particular, if @link(FileName) was not set yet). }
    function FindTextureBaseName(const TextureBaseName: string): TMaterialProperty;
  end;

{ Known material properties.
  Set the @link(TMaterialProperties.FileName FileName) property
  to load material properties from XML file. }
function MaterialProperties: TMaterialProperties;

implementation

uses SysUtils, XMLRead, CastleXMLUtils, CastleFilesUtils, X3DNodes;

{ TMaterialProperty --------------------------------------------------------- }

procedure TMaterialProperty.LoadFromDOMElement(Element: TDOMElement; const BaseUrl: string);
var
  FootstepsSoundName: string;
  ToxicDamage: TDOMElement;
  I: TXMLElementIterator;
begin
  if not DOMGetAttribute(Element, 'texture_base_name', FTextureBaseName) then
    raise Exception.Create('<properties> element must have "texture_base_name" attribute');

  FootstepsSoundName := '';
  if DOMGetAttribute(Element, 'footsteps_sound', FootstepsSoundName) and
     (FootstepsSoundName <> '') then
    FFootstepsSound := SoundEngine.SoundFromName(FootstepsSoundName) else
    FFootstepsSound := stNone;

  if DOMGetAttribute(Element, 'normal_map', FNormalMap) and (FNormalMap <> '') then
    FNormalMap := CombinePaths(BaseUrl, FNormalMap) else
    FNormalMap := '';

  I := TXMLElementIterator.Create(Element);
  try
    while I.GetNext do
      if I.Current.TagName = 'toxic' then
      begin
        FToxic := true;
        ToxicDamage := DOMGetOneChildElement(I.Current);
        if (ToxicDamage = nil) or (ToxicDamage.TagName <> 'damage') then
          raise Exception.Create('Missing <damage> inside <toxic> element');
        if not DOMGetSingleAttribute(ToxicDamage, 'const', FToxicDamageConst) then
          FToxicDamageConst := 0;
        if not DOMGetSingleAttribute(ToxicDamage, 'random', FToxicDamageRandom) then
          FToxicDamageRandom := 0;
        if not DOMGetSingleAttribute(ToxicDamage, 'time', FToxicDamageTime) then
          FToxicDamageTime := 0;
      end else
        raise Exception.CreateFmt('Unknown element inside <property>: "%s"',
          [I.Current.TagName]);
  finally FreeAndNil(I) end;
end;

{ TMaterialProperties ---------------------------------------------------------- }

procedure TMaterialProperties.SetFileName(const Value: string);
var
  Config: TXMLDocument;
  Element: TDOMElement;
  Elements: TDOMNodeList;
  MaterialProperty: TMaterialProperty;
  I: Integer;
begin
  FFileName := Value;

  Clear;

  try
    { ReadXMLFile always sets TXMLDocument param (possibly to nil),
      even in case of exception. So place it inside try..finally. }
    ReadXMLFile(Config, FileName);

    Check(Config.DocumentElement.TagName = 'properties',
      'Root node of material properties file must be <properties>');

    Elements := Config.DocumentElement.ChildNodes;
    try
      for I := 0 to Elements.Count - 1 do
        if Elements.Item[I].NodeType = ELEMENT_NODE then
        begin
          Element := Elements.Item[I] as TDOMElement;
          Check(Element.TagName = 'property',
            'Material properties file must be a sequence of <property> elements');

          MaterialProperty := TMaterialProperty.Create;
          Add(MaterialProperty);

          MaterialProperty.LoadFromDOMElement(Element, ExtractFilePath(FileName));
        end;
    finally FreeChildNodes(Elements); end;
  finally
    SysUtils.FreeAndNil(Config);
  end;
end;

function TMaterialProperties.FindTextureBaseName(const TextureBaseName: string): TMaterialProperty;
var
  I: Integer;
begin
  for I := 0 to Count - 1 do
    if SameText(Items[I].TextureBaseName, TextureBaseName) then
      Exit(Items[I]);
  Result := nil;
end;

var
  FMaterialProperties: TMaterialProperties;

function MaterialProperties: TMaterialProperties;
begin
  if FMaterialProperties = nil then
    FMaterialProperties := TMaterialProperties.Create(true);
  Result := FMaterialProperties;
end;

finalization
  FreeAndNil(FMaterialProperties);
end.