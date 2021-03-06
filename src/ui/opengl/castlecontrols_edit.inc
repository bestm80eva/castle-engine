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

{$ifdef read_interface}

  { Edit box to input 1 line of text. }
  TCastleEdit = class(TUIControlFont)
  strict private
    FText: string;
    FPaddingHorizontal, FPaddingVertical, FPadding: Integer;
    FBackgroundColor, FFocusedColor, FUnfocusedColor: TCastleColor;
    FFrame: boolean;
    FWidth: Cardinal;
    LifeTime: TFloatTime;
    FMaxLength: Cardinal;
    FAllowedChars: TSetOfChars;
    FCaptureAllInput: boolean;
    Scissor: TScissor;
    procedure SetText(const Value: string);
    procedure SetFocusedColor(const Value: TCastleColor);
    procedure SetUnfocusedColor(const Value: TCastleColor);
    procedure SetBackgroundColor(const Value: TCastleColor);
    procedure SetWidth(const Value: Cardinal);
    procedure SetPadding(const Value: Integer);
    procedure SetPaddingHorizontal(const Value: Integer);
    procedure SetPaddingVertical(const Value: Integer);
    procedure SetFrame(const Value: boolean);
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure Render; override;
    function Rect: TRectangle; override;
    function Press(const Event: TInputPressRelease): boolean; override;
    procedure Update(const SecondsPassed: Single;
      var HandleInput: boolean); override;
    function CapturesEventsAtPosition(const Position: TVector2Single): boolean; override;

    { Focused text color. By default it's black. }
    property FocusedColor: TCastleColor read FFocusedColor write SetFocusedColor;

    { Unfocused text color. By default it's dark gray. }
    property UnfocusedColor: TCastleColor read FUnfocusedColor write SetUnfocusedColor;

    { Background color. Fills the area under @link(Text) and the padding.
      By default it's white.
      Note that it can be transparent, in which case it will show the
      tiEdit image underneath (if @link(Frame) is @true),
      or UI control underneath (if @link(Frame) is @false). }
    property BackgroundColor: TCastleColor read FBackgroundColor write SetBackgroundColor;

    { Allowed characters that user can input.
      Note that this @italic(only restricts the user input),
      it does not prevent from programmatically setting @link(Text)
      to include disallowed characters. }
    property AllowedChars: TSetOfChars read FAllowedChars write FAllowedChars;

    { Max length of user input.
      Value of 0 (default) means "no limit".
      Note that this @italic(only restricts the user input),
      it does not prevent from programmatically setting @link(Text)
      to be longer. }
    property MaxLength: Cardinal read FMaxLength write FMaxLength;
  published
    const
      DefaultWidth = 100;
      DefaultPadding = 4;

    { Width, in pixels.

      Inside it, we will put the border frame (if @link(Frame) is @true),
      and padding (see @link(Padding) + @link(PaddingHorizontal)).
      So, similar to CSS box model called box-sizing, width includes also
      padding and border.

      Note that the edit control width is never auto-calculated,
      since there's no "natural width" for the edit box.
      In contrast, our height is always (for now) auto-calculated. }
    property Width: Cardinal read FWidth write SetWidth default DefaultWidth;

    { Currently input text. }
    property Text: string read FText write SetText;

    { Inside the box rectangle, padding between the borders (or frame, if @link(Frame)) and text.
      Total horizontal padding is the sum @code(PaddingHorizontal + Padding),
      total vertical padding is the sum @code(PaddingVertical + Padding).
      @groupBegin }
    property PaddingHorizontal: Integer
      read FPaddingHorizontal write SetPaddingHorizontal default 0;
    property PaddingVertical: Integer
      read FPaddingVertical write SetPaddingVertical default 0;
    property Padding: Integer
      read FPadding write SetPadding default DefaultPadding;
    { @groupEnd }

    { Draw frame around the box. Frame uses theme image tiEdit,
      see TCastleTheme.Images if you want to customize it. }
    property Frame: boolean read FFrame write SetFrame default true;

    { Should we capture input regardless of the currently focused control.
      This is in practice only sensible if this is the only edit box currently
      visible on the screen. }
    property CaptureAllInput: boolean read FCaptureAllInput write FCaptureAllInput;
  end;

{$endif read_interface}

{$ifdef read_implementation}

{ TCastleEdit --------------------------------------------------------------- }

constructor TCastleEdit.Create(AOwner: TComponent);
begin
  inherited;
  FFocusedColor := Black;
  FUnfocusedColor := Vector4Single(0.25, 0.25, 0.25, 1);
  FBackgroundColor := White;
  FWidth := DefaultWidth;
  FPadding := DefaultPadding;
  FFrame := true;
  FAllowedChars := AllChars;
  FMaxLength := 0;
  Scissor := TScissor.Create;
end;

destructor TCastleEdit.Destroy;
begin
  FreeAndNil(Scissor);
  inherited;
end;

procedure TCastleEdit.SetText(const Value: string);
begin
  if FText <> Value then
  begin
    FText := Value;
    VisibleChange;
  end;
end;

procedure TCastleEdit.SetFocusedColor(const Value: TCastleColor);
begin
  if not VectorsPerfectlyEqual(FFocusedColor, Value) then
  begin
    FFocusedColor := Value;
    VisibleChange;
  end;
end;

procedure TCastleEdit.SetUnfocusedColor(const Value: TCastleColor);
begin
  if not VectorsPerfectlyEqual(FUnfocusedColor, Value) then
  begin
    FUnfocusedColor := Value;
    VisibleChange;
  end;
end;

procedure TCastleEdit.SetBackgroundColor(const Value: TCastleColor);
begin
  if not VectorsPerfectlyEqual(FBackgroundColor, Value) then
  begin
    FBackgroundColor := Value;
    VisibleChange;
  end;
end;

procedure TCastleEdit.SetWidth(const Value: Cardinal);
begin
  if FWidth <> Value then
  begin
    FWidth := Value;
    VisibleChange;
  end;
end;

procedure TCastleEdit.SetPadding(const Value: Integer);
begin
  if FPadding <> Value then
  begin
    FPadding := Value;
    VisibleChange;
  end;
end;

procedure TCastleEdit.SetPaddingHorizontal(const Value: Integer);
begin
  if FPaddingHorizontal <> Value then
  begin
    FPaddingHorizontal := Value;
    VisibleChange;
  end;
end;

procedure TCastleEdit.SetPaddingVertical(const Value: Integer);
begin
  if FPaddingVertical <> Value then
  begin
    FPaddingVertical := Value;
    VisibleChange;
  end;
end;

procedure TCastleEdit.SetFrame(const Value: boolean);
begin
  if FFrame <> Value then
  begin
    FFrame := Value;
    VisibleChange;
  end;
end;

function TCastleEdit.Rect: TRectangle;
var
  PaddingVerticalScaled, HeightScaled: Integer;
  US: Single;
  FrameCorners: TVector4Integer;
begin
  US := UIScale;
  PaddingVerticalScaled := Round(US * (PaddingVertical + Padding));

  HeightScaled := Font.RowHeight + 2 * PaddingVerticalScaled;
  if Frame then
  begin
    FrameCorners := Theme.Corners[tiEdit];
    HeightScaled := HeightScaled + Round(US * FrameCorners[0]) + Round(US * FrameCorners[2]);
  end;

  Result := Rectangle(LeftBottomScaled, Round(Width * US), HeightScaled);
end;

procedure TCastleEdit.Render;
const
  CaretSpeed = 1; //< how many blinks per second
var
  SR, RectInside: TRectangle;
  PaddingHorizontalScaled, PaddingVerticalScaled: Integer;
  US: Single;
  FrameCorners: TVector4Integer;
  CaretVisible: boolean;
  S: string;
  Color: TCastleColor;
begin
  inherited;

  SR := ScreenRect;
  US := UIScale;
  RectInside := SR;

  if Frame then
  begin
    { make smaller RectInside, by frame size }
    FrameCorners := Theme.Corners[tiEdit];
    RectInside := RectInside.
      RemoveTop(FrameCorners[0]).
      RemoveRight(FrameCorners[1]).
      RemoveBottom(FrameCorners[2]).
      RemoveLeft(FrameCorners[3]);

    { draw frame }
    Theme.Draw(SR, tiEdit, US);
  end;

  { fill padding and area under Text with BackgroundColor }
  DrawRectangle(RectInside, BackgroundColor);

  { make smaller RectInside, by padding }
  PaddingHorizontalScaled := Round(US * (PaddingHorizontal + Padding));
  PaddingVerticalScaled := Round(US * (PaddingVertical + Padding));
  RectInside := RectInside.Grow(-PaddingHorizontalScaled, -PaddingVerticalScaled);

  S := Text;
  if Focused then
  begin
    CaretVisible := FloatModulo(LifeTime * CaretSpeed, 1.0) < 0.5;
    if CaretVisible then
      S := S + CaretChar;
    Color := FocusedColor;
  end else
    Color := UnfocusedColor;

  Scissor.Rect := RectInside;
  Scissor.Enabled := true;

  Font.Print(RectInside.Left, RectInside.Bottom + Font.Descend, Color, S);

  Scissor.Enabled := false;
end;

procedure TCastleEdit.Update(const SecondsPassed: Single;
  var HandleInput: boolean);
begin
  inherited;
  LifeTime += SecondsPassed;
end;

function TCastleEdit.Press(const Event: TInputPressRelease): boolean;
begin
  Result := inherited;
  if Result or (not GetExists) then Exit;

  if Event.IsKey(CharBackSpace) or Event.IsKey(K_BackSpace) then
  begin
    if Text <> '' then
      Text := Copy(Text, 1, Length(Text) - 1);
  end else
(*
  // TODO: Expose Clipboard in UI controls that don't depend on CastleWindow.
  if Event.IsKey(CtrlC) then
  begin
    if Text <> '' then
      Clipboard.AsText := Text;
  end else
  if Event.IsKey(CtrlX) then
  begin
    if Text <> '' then
    begin
      Clipboard.AsText := Text;
      Text := '';
    end;
  end else
  if Event.IsKey(CtrlV) then
  begin
    Text := SDeleteChars(Clipboard.AsText, AllChars - FAllowedChars);
  end else
*)
  if (Event.EventType = itKey) and
     (Event.KeyCharacter <> #0) and
     (Event.KeyCharacter in AllowedChars) and
     ((MaxLength = 0) or (Length(Text) < MaxLength)) then
  begin
    Text := Text + Event.KeyCharacter;
  end;
end;

function TCastleEdit.CapturesEventsAtPosition(const Position: TVector2Single): boolean;
begin
  if CaptureAllInput then
    Result := true // always capture
  else
    Result := inherited CapturesEventsAtPosition(Position);
end;

{$endif read_implementation}
