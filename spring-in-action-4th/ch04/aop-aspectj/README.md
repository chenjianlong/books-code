## 说明

需要使用 mvn build 或者 mvn clean 命令，直接使用 IDEA CE 的 Build 命令，然后运行会报错，原因是默认不会织入 CriticAspect.aj,
可通过菜单 View->Tool Windows->Maven 然后 compile 或者 package，织入 CriticAspect.aj 后，再运行。