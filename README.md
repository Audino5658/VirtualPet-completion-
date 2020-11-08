# VirtualPet-Qubie-
An AR Android app that you can have interactions or play games with a virtual pet


1.	概要：バーチャルペットを通して、インターラクティヴゲームを体験できるARアプリを実現するプロジェクト。
2.	開発期間：2013.8 ~ 2014.01
3.	開発メンバー数：三人
4.	使用ツール：Eclipse (Java, JavaScript, C), Android SDK, Android NDK, Vuforia SDK, 3ds max 2011
5.	自身の担当範囲：アニメーション、GUIの制作とプログラムの統合。
6.  担当部分の説明：外側のGUI処理から内部の3D画像処理それぞれは異なる言語で書かれたものですので、JNI（Java Native Interface）を通じてJava言語とC言語を連携しなければなりません。自分は主にこの二つ違うコードを整理しました。すなわち、Javaで書かれたGUIデータを内部のCコードに転送し、C言語のOpenGL ESで書かれた3DCGのデータまたJava側に転送するということです。このプロジェクトはゲームエンジンを使わずに3D APIでアニメションと3Dモデルの読み込みなどのグラフィック処理を実現しました。

7.	使用方法：USBケーブルを用いてAndroidスマホとパソコン繋がり、eclipseでプロジェクトを実行したらアプリはスマホで使用できます。しかし、特定のオブジェクトを作る必要がありますので、フォルダ内のPDFファイル“FlakesBox”を印刷し、アプリのターゲットとして使ってください。

8.	ビデオリンク：https://drive.google.com/open?id=0B-2wbF5_q5d0NlFjOWdRM0lOUGs
