{
  Copyright 2007-2011 Michalis Kamburelis.

  This file is part of "the rift".

  "the rift" is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  "the rift" is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with "the rift"; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  ----------------------------------------------------------------------------
}

{ }
unit RiftSound;

interface

uses XmlSoundEngine;

const
  MinorNonSpatialSoundImportance = 100;

var
  stIntroMusic,
  stMainMenuMusic,
  stMenuCurrentItemChanged,
  stMenuClick
  : TSoundType;

type
  TRiftSoundEngine = class(TXmlSoundEngine)
  public
    constructor Create;
    destructor Destroy; override;
  end;

function SoundEngine: TRiftSoundEngine;

implementation

uses SysUtils, ALSoundEngine, RiftConfig;

constructor TRiftSoundEngine.Create;

  procedure SoundNameType(const Name: string; var Value: TSoundType);
  begin
    SoundNames.Append(Name);
    Value := SoundFromName(Name);
    Assert(Integer(Value) = SoundNames.Count - 1);
  end;

begin
  inherited;

  SoundNameType('intro_music',             stIntroMusic);
  SoundNameType('main_menu_music',         stMainMenuMusic);
  SoundNameType('menu_current_item_changed',  stMenuCurrentItemChanged);
  SoundNameType('menu_current_item_selected', stMenuClick);

  AddSoundImportanceName('minor_non_spatial', MinorNonSpatialSoundImportance);

  LoadFromConfig(UserConfig);
end;

destructor TRiftSoundEngine.Destroy;
begin
  if UserConfig <> nil then
    SaveToConfig(UserConfig);

  inherited;
end;

function SoundEngine: TRiftSoundEngine;
begin
  Result := ALSoundEngine.SoundEngine as TRiftSoundEngine;
end;

{ initialization ------------------------------------------------------------- }

initialization
  ALSoundEngine.SoundEngine := TRiftSoundEngine.Create;
end.