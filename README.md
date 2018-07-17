# VirtualPet-Qubie-
An AR Android app that you can have interactions or play games with a virtual pet


1.	概要：バーチャルペットを通して、インターラクティヴゲームを体験できるARアプリを実現するプロジェクト。
2.	開発期間：2013.8 ~ 2014.01
3.	開発メンバー数：三人
4.	使用ツール：Eclipse (Java, JavaScript, C), Android SDK, Android NDK, Vuforia SDK, 3ds max 2011
5.	自身の担当範囲：アニメーション、GUIの制作とプログラムの統合。
6.	アピールポイント：外側のGUI処理から内部の３D画像処理それぞれは異なる言語で書かれたものですので、JNI（Java Native Interface）を通じてJava言語とC言語を連携しなければなりません。自分は主にこの二つ違うコードを整理していました。例えば、Javaで書かれたGUIデータを内部のCコードに転送し、C言語のOpenGL ESで書かれた3D映像のデータをJava側に返還します。また、このプロジェクトはゲームエンジンを使わずにグラフィックスを生成しましたので、そのところは手間かかて手書きのプログラムでアニメションと３Dモデルの読み込みを実現しました。そのため、内部グラフィックス演算についてもっと詳しくなりました。

7.	使用方法：USBケーブルを用いてAndroidスマホとパソコン繋がり、eclipseでプロジェクトを実行したらアプリはスマホで使用できます。しかし、特定のオブジェクト(フォルダ内のPDFファイル“FlakesBox”)また必要ですので、もし手間かかり過ぎなら、紹介動画も提供されています。

8.	ビデオリンク：https://drive.google.com/open?id=0B-2wbF5_q5d0NlFjOWdRM0lOUGs
