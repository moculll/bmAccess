#pragma once

/*
* SDK generated by Dumper-7
*
* https://github.com/Encryqed/Dumper-7
*/

// Package: SimpleCharts

#include "Basic.hpp"

#include "SimpleCharts_structs.hpp"
#include "CoreUObject_structs.hpp"
#include "UMG_classes.hpp"


namespace SDK
{

// Class SimpleCharts.ChartBase
// 0x01E8 (0x0318 - 0x0130)
class UChartBase : public UWidget
{
public:
	bool                                          UseDirtyRect;                                      // 0x0130(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EChartTheme                                   Theme;                                             // 0x0131(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          AxisStyleWithTheme;                                // 0x0132(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_133[0x5];                                      // 0x0133(0x0005)(Fixing Size After Last Property [ Dumper-7 ])
	class FString                                 Title_text;                                        // 0x0138(0x0010)(Edit, BlueprintVisible, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          Title_show;                                        // 0x0148(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EPosition                                     Title_position;                                    // 0x0149(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_14A[0x2];                                      // 0x014A(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	int32                                         Title_fontSize;                                    // 0x014C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FColor                                 Title_color;                                       // 0x0150(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          Legend_show;                                       // 0x0154(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EPosition                                     Legend_position;                                   // 0x0155(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EOrient                                       Legend_orient;                                     // 0x0156(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_157[0x1];                                      // 0x0157(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	struct FColor                                 Legend_color;                                      // 0x0158(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                         Legend_fontSize;                                   // 0x015C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TArray<class FString>                         AxisData;                                          // 0x0160(0x0010)(Edit, BlueprintVisible, ZeroConstructor, NativeAccessSpecifierPublic)
	bool                                          IsXAxis;                                           // 0x0170(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          boundaryGap;                                       // 0x0171(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_172[0x6];                                      // 0x0172(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
	struct FAxisLabel                             XaxisLabel;                                        // 0x0178(0x0028)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	struct FLineStyle                             XaxisLine;                                         // 0x01A0(0x0010)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	struct FLineStyle                             XsplitLine;                                        // 0x01B0(0x0010)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	struct FAxisLabel                             YaxisLabel;                                        // 0x01C0(0x0028)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	struct FLineStyle                             YaxisLine;                                         // 0x01E8(0x0010)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	struct FLineStyle                             YsplitLine;                                        // 0x01F8(0x0010)(Edit, BlueprintVisible, NoDestructor, NativeAccessSpecifierPublic)
	ETooltipType                                  Tooltip_type;                                      // 0x0208(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	SimpleCharts::ETriggerType                    Tooltip_trigger;                                   // 0x0209(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_20A[0x2];                                      // 0x020A(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	struct FColor                                 Text_color;                                        // 0x020C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FColor                                 Tip_backgroundColor;                               // 0x0210(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          Use_custom_color;                                  // 0x0214(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_215[0x3];                                      // 0x0215(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	TArray<struct FColor>                         Custom_color;                                      // 0x0218(0x0010)(Edit, BlueprintVisible, ZeroConstructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_228[0xF0];                                     // 0x0228(0x00F0)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetAnim(bool Active);
	void SetAxis(bool XAxis, const TArray<class FString>& Axis_Data);
	void SetCustomColor(bool Active, const TArray<struct FColor>& Custom_color_0);
	void SetTheme(EChartTheme ChartTheme, bool Axis_Style_With_Theme);
	void SetTitle(const class FString& Text, bool Show, EPosition Position, int32 FontSize, const struct FLinearColor& Color);
	void SetTooltipStyle(SimpleCharts::ETriggerType Trigger, ETooltipType ToolTip, const struct FLinearColor& TextColor, const struct FLinearColor& BackgroundColor);
	void SetXAxisStyle(const struct FAxisLabel& Xaxis_Label, const struct FLineStyle& Xaxis_Line, const struct FLineStyle& Xsplit_Line);
	void SetYAxisStyle(const struct FAxisLabel& Yaxis_Label, const struct FLineStyle& Yaxis_Line, const struct FLineStyle& Ysplit_Line);
	void UpdateChart();

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"ChartBase">();
	}
	static class UChartBase* GetDefaultObj()
	{
		return GetDefaultObjImpl<UChartBase>();
	}
};
//static_assert(alignof(UChartBase) == 0x000008, "Wrong alignment on UChartBase");
//static_assert(sizeof(UChartBase) == 0x000318, "Wrong size on UChartBase");
//static_assert(offsetof(UChartBase, UseDirtyRect) == 0x000130, "Member 'UChartBase::UseDirtyRect' has a wrong offset!");
//static_assert(offsetof(UChartBase, Theme) == 0x000131, "Member 'UChartBase::Theme' has a wrong offset!");
//static_assert(offsetof(UChartBase, AxisStyleWithTheme) == 0x000132, "Member 'UChartBase::AxisStyleWithTheme' has a wrong offset!");
//static_assert(offsetof(UChartBase, Title_text) == 0x000138, "Member 'UChartBase::Title_text' has a wrong offset!");
//static_assert(offsetof(UChartBase, Title_show) == 0x000148, "Member 'UChartBase::Title_show' has a wrong offset!");
//static_assert(offsetof(UChartBase, Title_position) == 0x000149, "Member 'UChartBase::Title_position' has a wrong offset!");
//static_assert(offsetof(UChartBase, Title_fontSize) == 0x00014C, "Member 'UChartBase::Title_fontSize' has a wrong offset!");
//static_assert(offsetof(UChartBase, Title_color) == 0x000150, "Member 'UChartBase::Title_color' has a wrong offset!");
//static_assert(offsetof(UChartBase, Legend_show) == 0x000154, "Member 'UChartBase::Legend_show' has a wrong offset!");
//static_assert(offsetof(UChartBase, Legend_position) == 0x000155, "Member 'UChartBase::Legend_position' has a wrong offset!");
//static_assert(offsetof(UChartBase, Legend_orient) == 0x000156, "Member 'UChartBase::Legend_orient' has a wrong offset!");
//static_assert(offsetof(UChartBase, Legend_color) == 0x000158, "Member 'UChartBase::Legend_color' has a wrong offset!");
//static_assert(offsetof(UChartBase, Legend_fontSize) == 0x00015C, "Member 'UChartBase::Legend_fontSize' has a wrong offset!");
//static_assert(offsetof(UChartBase, AxisData) == 0x000160, "Member 'UChartBase::AxisData' has a wrong offset!");
//static_assert(offsetof(UChartBase, IsXAxis) == 0x000170, "Member 'UChartBase::IsXAxis' has a wrong offset!");
//static_assert(offsetof(UChartBase, boundaryGap) == 0x000171, "Member 'UChartBase::boundaryGap' has a wrong offset!");
//static_assert(offsetof(UChartBase, XaxisLabel) == 0x000178, "Member 'UChartBase::XaxisLabel' has a wrong offset!");
//static_assert(offsetof(UChartBase, XaxisLine) == 0x0001A0, "Member 'UChartBase::XaxisLine' has a wrong offset!");
//static_assert(offsetof(UChartBase, XsplitLine) == 0x0001B0, "Member 'UChartBase::XsplitLine' has a wrong offset!");
//static_assert(offsetof(UChartBase, YaxisLabel) == 0x0001C0, "Member 'UChartBase::YaxisLabel' has a wrong offset!");
//static_assert(offsetof(UChartBase, YaxisLine) == 0x0001E8, "Member 'UChartBase::YaxisLine' has a wrong offset!");
//static_assert(offsetof(UChartBase, YsplitLine) == 0x0001F8, "Member 'UChartBase::YsplitLine' has a wrong offset!");
//static_assert(offsetof(UChartBase, Tooltip_type) == 0x000208, "Member 'UChartBase::Tooltip_type' has a wrong offset!");
//static_assert(offsetof(UChartBase, Tooltip_trigger) == 0x000209, "Member 'UChartBase::Tooltip_trigger' has a wrong offset!");
//static_assert(offsetof(UChartBase, Text_color) == 0x00020C, "Member 'UChartBase::Text_color' has a wrong offset!");
//static_assert(offsetof(UChartBase, Tip_backgroundColor) == 0x000210, "Member 'UChartBase::Tip_backgroundColor' has a wrong offset!");
//static_assert(offsetof(UChartBase, Use_custom_color) == 0x000214, "Member 'UChartBase::Use_custom_color' has a wrong offset!");
//static_assert(offsetof(UChartBase, Custom_color) == 0x000218, "Member 'UChartBase::Custom_color' has a wrong offset!");

// Class SimpleCharts.AreaChart
// 0x0020 (0x0338 - 0x0318)
class UAreaChart final : public UChartBase
{
public:
	TArray<struct FAreaSeries>                    Series;                                            // 0x0318(0x0010)(Edit, BlueprintVisible, ZeroConstructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_328[0x10];                                     // 0x0328(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const TArray<struct FAreaSeries>& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"AreaChart">();
	}
	static class UAreaChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<UAreaChart>();
	}
};
//static_assert(alignof(UAreaChart) == 0x000008, "Wrong alignment on UAreaChart");
//static_assert(sizeof(UAreaChart) == 0x000338, "Wrong size on UAreaChart");
//static_assert(offsetof(UAreaChart, Series) == 0x000318, "Member 'UAreaChart::Series' has a wrong offset!");

// Class SimpleCharts.BarChart
// 0x0020 (0x0338 - 0x0318)
class UBarChart final : public UChartBase
{
public:
	TArray<struct FBarSeries>                     Series;                                            // 0x0318(0x0010)(Edit, BlueprintVisible, ZeroConstructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_328[0x10];                                     // 0x0328(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const TArray<struct FBarSeries>& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"BarChart">();
	}
	static class UBarChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<UBarChart>();
	}
};
//static_assert(alignof(UBarChart) == 0x000008, "Wrong alignment on UBarChart");
//static_assert(sizeof(UBarChart) == 0x000338, "Wrong size on UBarChart");
//static_assert(offsetof(UBarChart, Series) == 0x000318, "Member 'UBarChart::Series' has a wrong offset!");

// Class SimpleCharts.ChartWebBrowser
// 0x0048 (0x0178 - 0x0130)
class UChartWebBrowser final : public UWidget
{
public:
	FMulticastInlineDelegateProperty_             OnUrlChanged;                                      // 0x0130(0x0010)(ZeroConstructor, InstancedReference, BlueprintAssignable, NativeAccessSpecifierPublic)
	FMulticastInlineDelegateProperty_             OnBeforePopup;                                     // 0x0140(0x0010)(ZeroConstructor, InstancedReference, BlueprintAssignable, NativeAccessSpecifierPublic)
	class FString                                 InitialURL;                                        // 0x0150(0x0010)(Edit, ZeroConstructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	bool                                          bSupportsTransparency;                             // 0x0160(0x0001)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	bool                                          bSupportIEM;                                       // 0x0161(0x0001)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uint8                                         Pad_162[0x16];                                     // 0x0162(0x0016)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void ExecuteJavascript(const class FString& ScriptText);
	void LoadString(const class FString& Contents, const class FString& DummyURL);
	void LoadURL(const class FString& NewURL);
	void OnBeforePopup__DelegateSignature(const class FString& URL, const class FString& Frame);
	void OnUrlChanged__DelegateSignature(const class FText& Text);

	class FText GetTitleText() const;
	class FString GetUrl() const;

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"ChartWebBrowser">();
	}
	static class UChartWebBrowser* GetDefaultObj()
	{
		return GetDefaultObjImpl<UChartWebBrowser>();
	}
};
//static_assert(alignof(UChartWebBrowser) == 0x000008, "Wrong alignment on UChartWebBrowser");
//static_assert(sizeof(UChartWebBrowser) == 0x000178, "Wrong size on UChartWebBrowser");
//static_assert(offsetof(UChartWebBrowser, OnUrlChanged) == 0x000130, "Member 'UChartWebBrowser::OnUrlChanged' has a wrong offset!");
//static_assert(offsetof(UChartWebBrowser, OnBeforePopup) == 0x000140, "Member 'UChartWebBrowser::OnBeforePopup' has a wrong offset!");
//static_assert(offsetof(UChartWebBrowser, InitialURL) == 0x000150, "Member 'UChartWebBrowser::InitialURL' has a wrong offset!");
//static_assert(offsetof(UChartWebBrowser, bSupportsTransparency) == 0x000160, "Member 'UChartWebBrowser::bSupportsTransparency' has a wrong offset!");
//static_assert(offsetof(UChartWebBrowser, bSupportIEM) == 0x000161, "Member 'UChartWebBrowser::bSupportIEM' has a wrong offset!");

// Class SimpleCharts.CustomChart
// 0x0058 (0x0188 - 0x0130)
class UCustomChart final : public UWidget
{
public:
	bool                                          UseDirtyRect;                                      // 0x0130(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EChartTheme                                   Theme;                                             // 0x0131(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_132[0x6];                                      // 0x0132(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
	class FString                                 Option;                                            // 0x0138(0x0010)(Edit, BlueprintVisible, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_148[0x40];                                     // 0x0148(0x0040)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetOption(const class FString& InOption, const class FString& OtherCode);
	void SetTheme(EChartTheme ChartTheme);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"CustomChart">();
	}
	static class UCustomChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<UCustomChart>();
	}
};
//static_assert(alignof(UCustomChart) == 0x000008, "Wrong alignment on UCustomChart");
//static_assert(sizeof(UCustomChart) == 0x000188, "Wrong size on UCustomChart");
//static_assert(offsetof(UCustomChart, UseDirtyRect) == 0x000130, "Member 'UCustomChart::UseDirtyRect' has a wrong offset!");
//static_assert(offsetof(UCustomChart, Theme) == 0x000131, "Member 'UCustomChart::Theme' has a wrong offset!");
//static_assert(offsetof(UCustomChart, Option) == 0x000138, "Member 'UCustomChart::Option' has a wrong offset!");

// Class SimpleCharts.DoughnutChart
// 0x00C8 (0x03E0 - 0x0318)
class UDoughnutChart final : public UChartBase
{
public:
	uint8                                         Pad_318[0x8];                                      // 0x0318(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FDoughnutSeries                        Series;                                            // 0x0320(0x00B0)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	uint8                                         Pad_3D0[0x10];                                     // 0x03D0(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const struct FDoughnutSeries& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"DoughnutChart">();
	}
	static class UDoughnutChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<UDoughnutChart>();
	}
};
//static_assert(alignof(UDoughnutChart) == 0x000010, "Wrong alignment on UDoughnutChart");
//static_assert(sizeof(UDoughnutChart) == 0x0003E0, "Wrong size on UDoughnutChart");
//static_assert(offsetof(UDoughnutChart, Series) == 0x000320, "Member 'UDoughnutChart::Series' has a wrong offset!");

// Class SimpleCharts.FunnelChart
// 0x0050 (0x0368 - 0x0318)
class UFunnelChart final : public UChartBase
{
public:
	struct FFunnelSeries                          Series;                                            // 0x0318(0x0040)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	uint8                                         Pad_358[0x10];                                     // 0x0358(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const struct FFunnelSeries& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"FunnelChart">();
	}
	static class UFunnelChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<UFunnelChart>();
	}
};
//static_assert(alignof(UFunnelChart) == 0x000008, "Wrong alignment on UFunnelChart");
//static_assert(sizeof(UFunnelChart) == 0x000368, "Wrong size on UFunnelChart");
//static_assert(offsetof(UFunnelChart, Series) == 0x000318, "Member 'UFunnelChart::Series' has a wrong offset!");

// Class SimpleCharts.GaugeChart
// 0x0038 (0x0350 - 0x0318)
class UGaugeChart final : public UChartBase
{
public:
	struct FGaugeSeries                           Series;                                            // 0x0318(0x0028)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	uint8                                         Pad_340[0x10];                                     // 0x0340(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const struct FGaugeSeries& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"GaugeChart">();
	}
	static class UGaugeChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<UGaugeChart>();
	}
};
//static_assert(alignof(UGaugeChart) == 0x000008, "Wrong alignment on UGaugeChart");
//static_assert(sizeof(UGaugeChart) == 0x000350, "Wrong size on UGaugeChart");
//static_assert(offsetof(UGaugeChart, Series) == 0x000318, "Member 'UGaugeChart::Series' has a wrong offset!");

// Class SimpleCharts.LineBarChart
// 0x0020 (0x0338 - 0x0318)
class ULineBarChart final : public UChartBase
{
public:
	TArray<struct FLineBarSeries>                 Series;                                            // 0x0318(0x0010)(Edit, BlueprintVisible, ZeroConstructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_328[0x10];                                     // 0x0328(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const TArray<struct FLineBarSeries>& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"LineBarChart">();
	}
	static class ULineBarChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<ULineBarChart>();
	}
};
//static_assert(alignof(ULineBarChart) == 0x000008, "Wrong alignment on ULineBarChart");
//static_assert(sizeof(ULineBarChart) == 0x000338, "Wrong size on ULineBarChart");
//static_assert(offsetof(ULineBarChart, Series) == 0x000318, "Member 'ULineBarChart::Series' has a wrong offset!");

// Class SimpleCharts.LineChart
// 0x0020 (0x0338 - 0x0318)
class ULineChart final : public UChartBase
{
public:
	TArray<struct FLineSeries>                    Series;                                            // 0x0318(0x0010)(Edit, BlueprintVisible, ZeroConstructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_328[0x10];                                     // 0x0328(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const TArray<struct FLineSeries>& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"LineChart">();
	}
	static class ULineChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<ULineChart>();
	}
};
//static_assert(alignof(ULineChart) == 0x000008, "Wrong alignment on ULineChart");
//static_assert(sizeof(ULineChart) == 0x000338, "Wrong size on ULineChart");
//static_assert(offsetof(ULineChart, Series) == 0x000318, "Member 'ULineChart::Series' has a wrong offset!");

// Class SimpleCharts.PieChart
// 0x00B8 (0x03D0 - 0x0318)
class UPieChart final : public UChartBase
{
public:
	uint8                                         Pad_318[0x8];                                      // 0x0318(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FPieSeries                             Series;                                            // 0x0320(0x00A0)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	uint8                                         Pad_3C0[0x10];                                     // 0x03C0(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const struct FPieSeries& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"PieChart">();
	}
	static class UPieChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<UPieChart>();
	}
};
//static_assert(alignof(UPieChart) == 0x000010, "Wrong alignment on UPieChart");
//static_assert(sizeof(UPieChart) == 0x0003D0, "Wrong size on UPieChart");
//static_assert(offsetof(UPieChart, Series) == 0x000320, "Member 'UPieChart::Series' has a wrong offset!");

// Class SimpleCharts.RadarChart
// 0x00A8 (0x03C0 - 0x0318)
class URadarChart final : public UChartBase
{
public:
	uint8                                         Pad_318[0x8];                                      // 0x0318(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FRadarSeries                           Series;                                            // 0x0320(0x0060)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	struct FRadar                                 Radar;                                             // 0x0380(0x0020)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	uint8                                         Pad_3A0[0x20];                                     // 0x03A0(0x0020)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetRadar(const struct FRadar& RadarData);
	void SetSeries(const struct FRadarSeries& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"RadarChart">();
	}
	static class URadarChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<URadarChart>();
	}
};
//static_assert(alignof(URadarChart) == 0x000010, "Wrong alignment on URadarChart");
//static_assert(sizeof(URadarChart) == 0x0003C0, "Wrong size on URadarChart");
//static_assert(offsetof(URadarChart, Series) == 0x000320, "Member 'URadarChart::Series' has a wrong offset!");
//static_assert(offsetof(URadarChart, Radar) == 0x000380, "Member 'URadarChart::Radar' has a wrong offset!");

// Class SimpleCharts.SankeyChart
// 0x0088 (0x03A0 - 0x0318)
class USankeyChart final : public UChartBase
{
public:
	uint8                                         Pad_318[0x8];                                      // 0x0318(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	struct FSankeySeries                          Series;                                            // 0x0320(0x0070)(Edit, BlueprintVisible, NativeAccessSpecifierPublic)
	uint8                                         Pad_390[0x10];                                     // 0x0390(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const struct FSankeySeries& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"SankeyChart">();
	}
	static class USankeyChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<USankeyChart>();
	}
};
//static_assert(alignof(USankeyChart) == 0x000010, "Wrong alignment on USankeyChart");
//static_assert(sizeof(USankeyChart) == 0x0003A0, "Wrong size on USankeyChart");
//static_assert(offsetof(USankeyChart, Series) == 0x000320, "Member 'USankeyChart::Series' has a wrong offset!");

// Class SimpleCharts.ScatterChart
// 0x0020 (0x0338 - 0x0318)
class UScatterChart final : public UChartBase
{
public:
	TArray<struct FScatterSeries>                 Series;                                            // 0x0318(0x0010)(Edit, BlueprintVisible, ZeroConstructor, NativeAccessSpecifierPublic)
	uint8                                         Pad_328[0x10];                                     // 0x0328(0x0010)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void SetLegend(bool Show, EPosition Position, EOrient Orient, const struct FLinearColor& Color, int32 FontSize);
	void SetSeries(const TArray<struct FScatterSeries>& SeriesData);

public:
	static class UClass* StaticClass()
	{
		return StaticClassImpl<"ScatterChart">();
	}
	static class UScatterChart* GetDefaultObj()
	{
		return GetDefaultObjImpl<UScatterChart>();
	}
};
//static_assert(alignof(UScatterChart) == 0x000008, "Wrong alignment on UScatterChart");
//static_assert(sizeof(UScatterChart) == 0x000338, "Wrong size on UScatterChart");
//static_assert(offsetof(UScatterChart, Series) == 0x000318, "Member 'UScatterChart::Series' has a wrong offset!");

}
