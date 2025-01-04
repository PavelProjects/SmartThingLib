
#ifndef WEB_ASSETS_H
#define WEB_ASSETS_H

/*
  Build version: 0.0.0
  Build date: 2025-01-04T15:00:09.564Z
  Build branch: master
  Build commit: 460dc352268905c8c1dd91008ee58b536b1a7a0b
*/

#include "Features.h"

#if ENABLE_WEB_PAGE 
  const char* WEB_PAGE_MAIN = R"=====(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SmartThingDevice</title>
    <script type="module" crossorigin src="/assets/script.js"></script>
    <link rel="stylesheet" href="/assets/styles.css">
  </head>
  <body>
    <h1 class="header">SmartThing device control panel</h1>
    <div id="control-panel" class="bordered"></div>
    <div id="toasts-list" class="list"></div>
  </body>
  
</html>)=====";

  const char* STYLE_PAGE_MAIN = R"=====(:root{--nc0:#2e3440;--nc1:#3b4252;--nc2:#434c5e;--nc3:#4c566a;--nc9:#81a1c1;--nc11:#bf616a;--nc12:#d08770;--nc14:#a3be8c;--cb: var(--nc0);--cb-m: var(--nc1);--cb-s: var(--nc2);--cbo: var(--nc3);--rbo: .25em;--ct: rgb(236, 239, 244);--dg: 2px;--miw: 250px}*,*:before,*:after{box-sizing:border-box;margin:0;font-weight:400}body{min-height:100vh;color:var(--ct);background:var(--cb);line-height:1.6;font-family:Inter;font-size:15px}#control-panel{display:flex;flex-direction:row;column-gap:var(--dg);margin:0 auto;width:1000px;opacity:0;transition:.5s}#toasts-list{position:absolute;bottom:5px;right:5px;z-index:999}dialog{color:inherit;padding:0;margin:auto;background-color:var(--cb);border:1px solid var(--cbo);border-radius:var(--rbo)}dialog>div{width:100%;height:100%;padding:var(--dg)}::backdrop{opacity:.7;background-color:var(--nc2)}.header{text-align:center;text-decoration:none}.btn{background-color:#88c0d0;border-color:transparent;border-radius:var(--rbo);color:#3b4252}.btn:hover{opacity:.5;cursor:pointer}input,select{font-size:18px;background-color:var(--cb);color:var(--ct);outline:none;border:1px solid var(--cbo);border-radius:var(--rbo)}.bordered{border:solid 2px var(--cbo);border-radius:var(--rbo)}.container{display:flex;flex-direction:column;gap:var(--dg);height:100%}.field-container{display:grid;grid-template-columns:1fr 1fr;border-radius:var(--rbo)}.field-container{text-align:center}.field-container .input-with-slot{display:flex;flex-direction:row;border:1px solid var(--cbo);border-radius:var(--rbo)}.input-with-slot input{width:100%;border:none}.input-checkbox input[type=checkbox]{height:15px;width:15px}.list{display:flex;flex-direction:column;row-gap:var(--dg)}.required{background-color:#bd090033;color:#000}.menu-panel{display:flex;flex-direction:row;flex:1 0 auto}.menu-items{width:var(--miw);padding:2px}.menu-items h2{transition:.5s;cursor:pointer;border-radius:var(--rbo);padding:5px;text-align:center;word-wrap:break-word}.menu-items h2:hover{transition:.5s;background-color:var(--cb-m)}.menu-item-content{position:relative;width:calc(100% - var(--miw))}.menu-selected{background-color:var(--cb-s)}.controls-holder{margin-top:auto;display:flex;flex-direction:row;gap:var(--dg)}.controls-holder button{width:100%}.hook-header{flex:1 1 auto;display:flex;flex-direction:row;gap:var(--dg);position:relative}.hooks-list-view{max-height:80vh;overflow-y:auto;margin-top:var(--dg)}.hooks-list-view .container{border-top:1px solid var(--cbo)}.hook-view-controls{display:flex;flex-direction:row-reverse;column-gap:var(--dg);align-items:center}.toast{position:relative;border:1px;border-radius:var(--rbo);width:300px;min-height:50px;padding:5px;z-index:1000;text-align:center}.br{border-right:2px solid var(--cbo)}.action-container{width:100%;display:flex;flex-direction:row;column-gap:var(--dg);align-items:center})=====";

  const char* SCRIPT_PAGE_MAIN = R"=====(var e=Object.defineProperty,t=(t,n,i)=>(((t,n,i)=>{n in t?e(t,n,{enumerable:!0,configurable:!0,writable:!0,value:i}):t[n]=i})(t,"symbol"!=typeof n?n+"":n,i),i);const n=function(){const e="undefined"!=typeof document&&document.createElement("link").relList;return e&&e.supports&&e.supports("modulepreload")?"modulepreload":"preload"}(),i={},a=function(e,t,a){if(!t||0===t.length)return e();const o=document.getElementsByTagName("link");return Promise.all(t.map((e=>{if((e=function(e){return"/"+e}(e))in i)return;i[e]=!0;const t=e.endsWith(".css"),s=t?'[rel="stylesheet"]':"";if(!!a)for(let n=o.length-1;n>=0;n--){const i=o[n];if(i.href===e&&(!t||"stylesheet"===i.rel))return}else if(document.querySelector(`link[href="${e}"]${s}`))return;const c=document.createElement("link");return c.rel=t?"stylesheet":n,t||(c.as="script",c.crossOrigin=""),c.href=e,document.head.appendChild(c),t?new Promise(((t,n)=>{c.addEventListener("load",t),c.addEventListener("error",(()=>n(new Error(`Unable to preload CSS for ${e}`))))})):void 0}))).then((()=>e())).catch((e=>{const t=new Event("vite:preloadError",{cancelable:!0});if(t.payload=e,window.dispatchEvent(t),!t.defaultPrevented)throw e}))},o={header:(e,t="h1")=>{const n=document.createElement(t);return n.classList.add("header"),n.innerHTML=e,n},container:(e={bordered:!1})=>{const t=document.createElement("div");return t.classList.add("container"),e.bordered&&t.classList.add("bordered"),t},list:()=>{const e=document.createElement("div");return e.classList.add("list"),e},button:({id:e,label:t,title:n,labelElement:i="h2",onClick:a,danger:o=!1,visible:s=!0})=>{const c=document.createElement("button");e&&(c.id=e),c.classList.add("btn");const r=`<${i}>${t}</${i}>`;return c.innerHTML=r,n&&(c.title=n),a&&(c.onclick=async()=>{c.disabled=!0,c.innerHTML="Loading...";try{await a()}catch(e){console.error(e)}finally{c.innerHTML=r,c.disabled=!1}}),o&&(c.style.backgroundColor="var(--nc11)"),s||(c.style.display="none"),c},icon:({id:e,icon:t,title:n,onClick:i=()=>{},visible:a=!0})=>{const o=document.createElement("span");return e&&(o.id=e),o.ariaHidden=!0,o.role="img",o.innerHTML=`<svg fill="currentColor" width="24" height="24" viewBox="0 0 24 24">${t}</svg>`,a||(o.style.display="none"),n&&(o.title=n),o.style.cursor="pointer",o.onclick=i,o},input:({id:e,label:t,value:n,title:i,disabled:a=!1,type:o="text",slot:s,props:c={},min:r})=>{const d=document.createElement("div");d.classList.add("field-container");const l=document.createElement("h2");l.innerHTML=t,i&&(l.title=i);const p=document.createElement("div"),u=document.createElement("input");return e&&(u.id=e),u.disabled=a,u.type=o,"checkbox"==u.type?(p.classList.add("input-checkbox"),u.checked=n):(p.classList.add("input-with-slot"),u.value=n),void 0!==r&&(u.min=r),Object.entries(c).forEach((([e,t])=>u.setAttribute(e,t))),p.appendChild(u),s&&p.appendChild(s),d.append(l,p),d},combobox:({id:e,value:t,values:n,label:i,disabled:a=!1,onChange:o,props:s={}})=>{const r=document.createElement("div");if(r.classList.add("field-container"),i){const e=document.createElement("h2");e.innerHTML=i,r.appendChild(e)}const d=document.createElement("select");return e&&(d.id=e),d.disabled=a,d.appendChild(document.createElement("option")),o&&(d.onchange=()=>o(d.value)),Object.entries(s).forEach((([e,t])=>d.setAttribute(e,t))),r.append(d),c(r,n),t&&(d.value=t),r},tree:e=>{const t=document.createElement("ul");return Object.entries(e).forEach((([e,n])=>t.appendChild(r({key:e,value:n})))),t},controlsHolder:()=>{const e=document.createElement("div");return e.classList.add("controls-holder"),e},dialog:({id:e="dialog"})=>{const t=document.createElement("dialog");return t.id=e,t.onclick=()=>t.close(),[t,()=>t.showModal(),()=>t.close()]}},s={pencil:'<path d="M20.71,7.04C21.1,6.65 21.1,6 20.71,5.63L18.37,3.29C18,2.9 17.35,2.9 16.96,3.29L15.12,5.12L18.87,8.87M3,17.25V21H6.75L17.81,9.93L14.06,6.18L3,17.25Z"></path>',trash:'<path d="M19,4H15.5L14.5,3H9.5L8.5,4H5V6H19M6,19A2,2 0 0,0 8,21H16A2,2 0 0,0 18,19V7H6V19Z"></path>',cross:'<path d="M13.46,12L19,17.54V19H17.54L12,13.46L6.46,19H5V17.54L10.54,12L5,6.46V5H6.46L12,10.54L17.54,5H19V6.46L13.46,12Z"></path>',save:'<path d="M15,9H5V5H15M12,19A3,3 0 0,1 9,16A3,3 0 0,1 12,13A3,3 0 0,1 15,16A3,3 0 0,1 12,19M17,3H5C3.89,3 3,3.9 3,5V19A2,2 0 0,0 5,21H19A2,2 0 0,0 21,19V7L17,3Z"></path>',tube:'<path d="M7,2V4H8V18A4,4 0 0,0 12,22A4,4 0 0,0 16,18V4H17V2H7M11,16C10.4,16 10,15.6 10,15C10,14.4 10.4,14 11,14C11.6,14 12,14.4 12,15C12,15.6 11.6,16 11,16M13,12C12.4,12 12,11.6 12,11C12,10.4 12.4,10 13,10C13.6,10 14,10.4 14,11C14,11.6 13.6,12 13,12M14,7H10V4H14V7Z"></path>',timer:'<path d="M12,20A7,7 0 0,1 5,13A7,7 0 0,1 12,6A7,7 0 0,1 19,13A7,7 0 0,1 12,20M19.03,7.39L20.45,5.97C20,5.46 19.55,5 19.04,4.56L17.62,6C16.07,4.74 14.12,4 12,4A9,9 0 0,0 3,13A9,9 0 0,0 12,22C17,22 21,17.97 21,13C21,10.88 20.26,8.93 19.03,7.39M11,14H13V8H11M15,1H9V3H15V1Z"/>'};function c(e,t){if(!t)return;const n=e.getElementsByTagName("select")[0];if(!n)return void console.error("Can't find select in combobox");let i;i=Array.isArray(t)?t.map((e=>({key:e,caption:e}))):Object.entries(t).map((([e,t])=>({key:e,caption:t}))),i.forEach((({key:e,caption:t})=>{const i=document.createElement("option");i.value=e,i.innerHTML=t,n.appendChild(i)}))}const r=({key:e,value:t})=>{const n=document.createElement("li");return n.append(e+": ",d(t)),n},d=e=>{if(Array.isArray(e)){const t=document.createElement("ul");return e.forEach((e=>{const n=document.createElement("li");n.innerHTML=e,t.appendChild(n)})),t}if(e instanceof Object){const t=document.createElement("ul");return Object.entries(e).forEach((([e,n])=>{const i=document.createElement("li");i.appendChild(r({key:e,value:n})),t.appendChild(i)})),t}{const t=document.createElement("span");return t.innerHTML=e,t}};class l{constructor(e,n,i){t(this,"selected",{}),this.id=e,this.menuItems=n,this.placeholder=i}create(){const e=document.createElement("div");return e.classList.add("menu-panel"),this.viewDiv=document.createElement("div"),this.viewDiv.classList.add("menu-items","list","br"),this.viewDiv.id=this.id,Object.entries(this.menuItems).forEach((([e,{name:t,title:n}])=>{const i=document.createElement("h2");i.id=e,i.innerHTML=t,n&&(i.title=n),i.onclick=()=>this.open(e),this.viewDiv.appendChild(i)})),this.contentDiv=document.createElement("div"),this.contentDiv.classList.add("menu-item-content"),this.contentDiv.id=this.id+"-content",this.loadingTitle=o.header("Loading...","h2"),this.loadingTitle.style.display="none",this.contentDiv.appendChild(this.loadingTitle),e.append(this.viewDiv,this.contentDiv),e}open(e){var t;if((null==(t=this.selected)?void 0:t.name)===e)return void this.updateContent();const n=document.getElementById(e);if(!n)return void console.error("Failed to open menuItem id="+e+": element not found");this.selected.item&&(this.selected.item.classList.remove("menu-selected"),this.selected.content.style.display="none");let i=document.getElementById(e+"-content");i?i.style.display="":(i=this.createContent(e),this.contentDiv.appendChild(i)),n.classList.add("menu-selected"),this.selected.name=e,this.selected.item=n,this.selected.content=i}updateContent(){this.selected&&(this.selected.content.remove(),this.selected.content=this.createContent(this.selected.name),this.contentDiv.appendChild(this.selected.content))}createContent(e){const t=e+"-content",n=o.container();return n.id=t,this.menuItems[e].header&&n.appendChild(o.header(this.menuItems[e].header)),this.loadContent(n,e),n}async loadContent(e,t){try{this.loading(!0),e.appendChild(await this.menuItems[t].content()??o.container())}catch(n){console.error(n)}finally{this.loading(!1)}}loading(e){this.loadingTitle.style.display=e?"":"none"}}let{hostname:p}=window.location;"localhost"===p&&(p="192.168.1.11");const u="Something gone wrong",m="GET",h="PUT",v="POST",f="DELETE",y={features:()=>E({path:"/features"}),info:()=>E({path:"/info/system"}),actions:()=>E({path:"/actions/info"}),getWifi:()=>E({path:"/wifi"}),saveWifi:e=>E({path:"/wifi",method:v,payload:e}),saveName:e=>E({path:"/info/system",method:h,payload:{name:e}}),callAction:e=>E({path:"/actions/call",params:{name:e}}),updateActionSchedule:(e,t)=>E({method:h,path:"/actions/schedule",payload:{name:e,callDelay:t}}),sensors:()=>E({path:"/sensors"}),config:()=>E({path:"/config"}),saveConfig:e=>E({method:v,path:"/config",payload:e}),dropConfig:()=>E({method:f,path:"/config/delete/all"}),hooks:({sensor:e})=>E({path:"/hooks",params:{sensor:e}}),hooksTemplates:e=>E({path:"/hooks/templates",params:{sensor:e}}),createHook:({sensor:e,hook:t})=>E({path:"/hooks",method:v,payload:{sensor:e,hook:t}}),updateHook:({sensor:e,hook:t})=>E({path:"/hooks",method:h,payload:{sensor:e,hook:t}}),deleteHook:({sensor:e,id:t})=>E({path:"/hooks",method:f,params:{sensor:e,id:t}}),testHook:({sensor:e,id:t})=>E({path:"/hooks/test",params:{sensor:e,id:t}}),metrics:()=>E({path:"/metrics"}),restart:()=>E({path:"/danger/restart",method:v}),wipe:()=>E({path:"/danger/wipe",method:v})};function E({method:e=m,path:t,payload:n,params:i}){const a=new XMLHttpRequest;let o,s;const c=new Promise(((e,t)=>{o=e,s=t}));return a.onloadend=()=>{const e={data:a.response?JSON.parse(a.response):null,status:a.status};a.status<200||a.status>299?s(e):o(e)},a.open(e,`http://${p}${"/"!=t[0]?"/":""}${t}${function(e){if(!e||!Object.keys(e))return"";const t=Object.entries(e).map((([e,t])=>`${e}=${t}`));return t.length>0?"?"+t.join("&"):""}(i)}`,!0),a.setRequestHeader("Accept","application/json"),n&&a.setRequestHeader("Content-Type","application/json"),a.send(n?JSON.stringify(n):null),c}let b=0;const g={INFO:"info",SUCCESS:"success",WARNING:"warning",ERROR:"error"};function C(e){const t=document.getElementById(e);t&&t.remove()}function L({type:e=g.INFO,caption:t,description:n=""}){const i=document.createElement("div");i.classList.add("toast");const a="toast-"+b++;i.id=a,i.style.backgroundColor=function(e){switch(e){case g.ERROR:return"var(--nc11)";case g.WARNING:return"var(--nc12)";case g.SUCCESS:return"var(--nc14)";default:return"var(--nc9)"}}(e);const o=document.createElement("h2");o.id=a+"-caption",o.innerHTML=t;const s=document.createElement("div");s.id=a+"-description",s.style.overflowWrap="break-word",s.innerHTML=n,i.append(o,s),i.onclick=()=>C(a),document.getElementById("toasts-list").appendChild(i),setTimeout((()=>C(a)),5e3)}const w={info:({caption:e,description:t})=>L({caption:e,description:t}),error:({caption:e,description:t})=>L({type:g.ERROR,caption:e,description:t}),success:({caption:e,description:t})=>L({type:g.SUCCESS,caption:e,description:t}),warning:({caption:e,description:t})=>L({type:g.WARNING,caption:e,description:t})},H={info:{name:"Information",content:async()=>{const e=await y.info().then((({data:e})=>e)).catch((()=>w.error({caption:u,description:"Failed to fetch system information"})));if(!e)return;document.title=`SmartThing ${e.name}(${e.type})`;const t=o.list();return t.append(o.input({id:"device-name",label:"Device name",value:e.name||"",slot:o.button({id:"save-device-name",label:"save",onClick:async()=>{const e=document.getElementById("device-name"),t=e.value;if(!t||0===t.length)return e.classList.add("required"),void w.error({caption:"Device name can't be empty!"});await y.saveName(t).then((()=>w.success({caption:"Name updated",description:"New device name: "+t}))).catch((()=>w.error({caption:"Name update failed",description:"Failed to update device name"}))).finally((()=>e.classList.remove("required")))}})}),o.input({label:"Device type",value:e.type,disabled:!0}),o.input({label:"Ip",value:e.ip,disabled:!0}),o.input({label:"Board",value:e.board,disabled:!0}),o.input({label:"SmartThing version",value:e.stVersion,disabled:!0})),e.version&&t.append(o.input({label:"Firmware version",value:e.version,disabled:!0})),t.style.padding="2px",t}},wifi:{name:"WiFi",content:async()=>{const{settings:e,modes:t}=await y.getWifi().then((({data:e})=>e)).catch((()=>w.error({caption:u,description:"Failed to fetch WiFi settings"})));if(!e)return;const n=o.list();n.append(o.input({id:"ssid",label:"SSID",value:e.ssid||""}),o.input({id:"password",label:"password",value:e.password||""}),o.combobox({id:"mode",label:"mode",values:t,value:e.mode}));const i=o.controlsHolder();i.appendChild(o.button({label:"Save",onClick:async()=>{y.saveWifi({ssid:document.getElementById("ssid").value||"",password:document.getElementById("password").value||"",mode:document.getElementById("mode").value||""}).then((()=>w.success({caption:"WiFi settings updated",description:"Restart device to apply new settings"}))).catch((()=>w.error({caption:"Failed to update WiFi settings",description:"Check device logs for additional information"})))}}));const a=o.container();return a.append(n,i),a.style.padding="2px",a}},actions:async()=>{const{ActionsTab:e}=await a((()=>import("./actions.js")),[]);return e},sensors:async()=>{const{SensorsTab:e}=await a((()=>import("./sensors.js")),[]);return e},config:async()=>{const{ConfigTab:e}=await a((()=>import("./config.js")),[]);return e},metrics:{name:"Metrics",content:async()=>{const{data:e}=await y.metrics().catch((()=>w.error({caption:u,description:"Failed to fetch device metrics"})));return o.tree(e)}},danger:{name:"Danger zone",content:async()=>{const e=o.list();return e.appendChild(o.header("Please, be careful with this actions!")),e.append(o.button({id:"restart",label:"Restart device",labelElement:"h1",danger:!0,onClick:()=>{confirm("Are you sure you want to restart device right now?")&&y.restart().then((()=>w.success({caption:"Restarting",description:"Device is restarting, please wait"}))).catch((()=>w.error({caption:u})))}}),o.button({id:"wipe",label:"Wipe device settings",labelElement:"h1",danger:!0,onClick:()=>{confirm("THIS ACTIONS WILL DELETE ALL SETTINGS FROM DEVICE!")&&confirm("THERE IS NOY TO RESTORE THEM AFTER THIS ACTION!")&&confirm("THIS IS LAST CONFIRMATION")&&y.wipe().then((()=>w.success({caption:"Settings wiped",description:"Device is gonna restart now, please wait"}))).catch((()=>w.error({caption:u})))}})),e.style.padding="2px",e}}};window.addEventListener("DOMContentLoaded",(async()=>{const e=await y.features().catch((()=>{w.error({caption:"Failed to load device features"})})).then((({data:e})=>e))??{},t={};for(const[a,o]of Object.entries(H))void 0!==e[a]&&!0!==e[a]||(t[a]="function"==typeof o?await o().catch((()=>w.error({caption:"failed to load tab"}))):o);const n=new l("main-menu",t);window.features=e;const i=document.getElementById("control-panel");i.appendChild(n.create()),n.open("info"),i.style.opacity="1"}));export{o as C,y as D,u as F,s as I,l as M,a as _,c as f,w as t};)=====";

  const char* SCRIPT_ACTIONS_TAB = R"=====(import{D as a,t as e,C as t,I as n}from"./script.js";const o={name:"Actions",content:async()=>{const o=await a.actions().then((({data:a})=>a)).catch((()=>e.error({caption:"Failed to load actions"})));if(!o)return t.header("No actions configured");const c=t.list();return o.forEach((({name:o,caption:i,callDelay:l,lastCall:r})=>{var s;const d=t.container();d.classList.add("action-container");const p=t.button({id:"action_"+o,label:i,title:`System name: ${o}${l>0?"\nLast call ms ago: "+r:""}`,labelElement:"h1",onClick:()=>a.callAction(o).then((()=>e.success({caption:"Done"}))).catch((()=>e.error({caption:`Failed to perform action "${i}"`})))});if(p.style.width="100%",d.append(p),null==(s=window.features)?void 0:s.actionsScheduler){const[c,i,r]=t.dialog({id:"dialog-"+o});c.append(((n,o,c)=>{const i=t.container();i.onclick=a=>a.stopPropagation();const l=async t=>{t<0?(s.classList.add("required"),e.error({caption:"Delay can't be negative"})):a.updateActionSchedule(n,t).then((()=>{e.success({caption:0===t?"Delay disabled":"Delay updated"}),c()})).catch((()=>e.error({caption:"Failed to update delay"})))},r=n+"-action-delay",s=t.input({id:r,label:"Call every (ms)",value:o,type:"number",min:0}),d=t.button({label:"Disable delay",onClick:()=>confirm("Disable action delay?")&&l(0),danger:!0}),p=t.button({label:"Save",onClick:()=>{var a;return l(Number((null==(a=document.getElementById(r))?void 0:a.value)??0))}}),u=t.controlsHolder();return u.append(d,p),i.append(s,u),i})(o,l,r)),d.append(t.icon({icon:n.timer,onClick:i}),c)}c.append(d)})),c.style.padding="2px",c}};export{o as ActionsTab};)=====";

  const char* SCRIPT_SENSORS_TAB = R"=====(import{D as e,t as s,F as o,C as n,_ as t,M as r}from"./script.js";const a={name:"Sensors",content:async()=>{const{data:a}=await e.sensors().catch((()=>s.error({caption:o})));if(!a||0===Object.keys(a).length)return n.header("No sensors configured","h2");const i=Object.entries(a).reduce(((e,[s,o])=>(e["sensors-menu-"+s]={name:`${s}: ${o}`,title:"Click to open hooks",content:async()=>{var e,o;if(void 0===(null==(e=window.features)?void 0:e.hooks)||1==(null==(o=window.features)?void 0:o.hooks)){const{HooksView:e}=await t((()=>import("./hooks.js")),["assets/hooks.js","assets/script.js","assets/styles.css"]);return new e({id:"cb_view_"+s,sensor:s}).create()}return n.header("Hooks feature disabled in this build","h2")}},e)),{});return new r("sensors-menu",i).create()}};export{a as SensorsTab};)=====";

  const char* SCRIPT_HOOKS_TAB = R"=====(import{C as e,I as t,t as s,D as i,F as o,f as a}from"./script.js";function d(e){return"string"!=typeof e||0==e.length?"":e.split("").reduce(((e,t)=>("_"===t?e+=" ":t===t.toUpperCase()?e+=" "+t.toLowerCase():e+=t,e)),"")}const n=["id","type","readonly"];class h{constructor({id:s="",hook:i,template:o,sensor:a,parent:d}){this.id=s,this.hook=i,this.template=o,this.sensor=a,this.parent=d,this.fields=Object.entries(this.hook).filter((([e])=>!function(e){return n.includes(e)}(e))).reverse(),this.controls={test:e.icon({icon:t.tube,onClick:()=>this.test(),title:"Make a test hook call"}),delete:e.icon({icon:t.trash,onClick:()=>this.delete()}),edit:e.icon({icon:t.pencil,onClick:()=>this.edit()}),cancel:e.icon({icon:t.cross,onClick:()=>this.cancel(),visible:!1}),save:e.icon({icon:t.save,onClick:()=>this.save(),visible:!1})}}create(){const t=document.getElementById(this.id);if(this.id&&t)return t;const s=e.container();s.id=this.id;const i=document.createElement("div");i.classList.add("hook-header");const{id:o,caption:a,type:n}=this.hook,h=e.header(`[${o}] ${a||d(n)}`,"h2");h.classList.add("hook-header");const c=document.createElement("div");c.classList.add("hook-view-controls"),Object.values(this.controls).forEach((e=>c.appendChild(e))),i.append(h,c);const l=e.list();return this.fields.forEach((([t,s])=>{const i={id:`${this.id}_${t}`,label:d(t),disabled:!0,type:"text",value:s,props:{required:!1}};let o;if(this.template[t]){const{required:e,type:s,values:o}=this.template[t];i.required=e,s&&(i.type=s),o&&(i.values=o),i.props.required=e??!1}o=i.values?e.combobox(i):e.input(i),l.appendChild(o)})),s.append(i,l),s}edit(e=!0){this.fields.forEach((([t])=>{document.getElementById(`${this.id}_${t}`).disabled=!e})),e?(this.controlsVisibile(["cancel","save"],!0),this.controlsVisibile(["delete","edit","test"],!1)):(this.controlsVisibile(["cancel","save"],!1),this.controlsVisibile(["delete","edit","test"],!0))}controlsVisibile(e,t){e.forEach((e=>this.controls[e].style.display=t?"":"none"))}validate(){let e=!0;return this.fields.forEach((([t])=>{const s=document.getElementById(`${this.id}_${t}`);"true"!=s.getAttribute("required")||s.value||(e=!1,s.classList.add("required"))})),e}async save(){if(!this.validate())return;let e;this.fields.forEach((([e])=>{const{checked:t,value:s}=document.getElementById(`${this.id}_${e}`);this.hook[e]="triggerEnabled"===e?t:s})),"New"===this.hook.id?(delete this.hook.id,e=i.createHook):e=i.updateHook,await e({sensor:this.sensor,hook:this.hook}).then((()=>{s.success({caption:`Hook ${"New"===this.hook.id?"created":"updated"}!`}),document.getElementById(this.id).remove(),this.parent.update()})).catch((()=>s.error({caption:"Failed to save hook",description:"Check device logs for additional information"})))}async delete(){confirm("Are you sure you wan to delete hook "+this.hook.id+"?")&&await i.deleteHook({sensor:this.sensor,id:this.hook.id}).then((()=>{s.success({caption:"Hook deleted"}),this.parent.update()})).catch((()=>s.error({caption:"Failed to delete hook",description:"Check device logs for additional information"})))}async test(){await i.testHook({sensor:this.sensor,id:this.hook.id}).then((()=>s.success({caption:"Hook called successfully!"}))).catch((()=>s.error({caption:"Failed to call hook"})))}cancel(){"New"===this.hook.id?(document.getElementById(this.id).remove(),this.parent.update()):this.edit(!1)}}class c{constructor({id:e="",sensor:t}){this.id=e,this.sensor=t}create(){const t=document.getElementById(this.id);if(this.id&&t)return t;const s=document.createElement("div");return s.id=this.id,s.style.padding="2px",this.comboboxTemplates=e.combobox({values:[],label:"Add hook of type",onChange:e=>{this.addNewHook(e)}}),this.list=e.list(),this.list.id="cb_list_"+this.id,this.list.classList.add("hooks-list-view"),s.append(this.comboboxTemplates,this.list),this.firstLoad(),s}update(){this.loadHooks()}async firstLoad(){await this.loadTemplates(),this.loadHooks()}async loadTemplates(){this.templates=await i.hooksTemplates(this.sensor).then((({data:e})=>e)).catch((()=>s.error({caption:o}))),this.templates&&a(this.comboboxTemplates,Object.keys(this.templates).filter((e=>"default"!==e)).reduce(((e,t)=>(e[t]=d(t),e)),{}))}async loadHooks(){this.list.innerHTML="",this.hooks=await i.hooks({sensor:this.sensor}).then((({data:e})=>e)).catch((()=>s.error({caption:o}))),this.hooks&&0!==this.hooks.length?this.hooks.forEach((e=>this.list.appendChild(new h({id:`${this.sensor}_hook_${e.id}`,hook:e,template:{...this.templates[e.type],...this.templates.default},sensor:this.sensor,parent:this}).create()))):this.list.appendChild(e.header("No hooks added yet","h3"))}addNewHook(e){const t=document.getElementById("cb_new");if(t&&t.remove(),!e)return;const s={...this.templates[e],...this.templates.default},i=Object.entries(s).reduce(((e,[t,s])=>(e[t]=s.default||"",e)),{id:"New",type:e}),o=new h({id:"cb_new",hook:i,template:s,sensor:this.sensor,parent:this});this.list.prepend(o.create()),o.edit()}}export{h as HookView,c as HooksView};)=====";

  const char* SCRIPT_CONFIG_TAB = R"=====(import{D as e,t,C as n}from"./script.js";const a=e=>`config_${e}`,o={name:"Configuration",content:async()=>{const o=await e.config().then((({data:e})=>e??{})).catch((()=>t.error({caption:"Failed to fetch configuration values"})));if(0===Object.keys(o).length)return n.header("No config entries","h2");const c=Object.entries(o).map((([e,t])=>n.input({id:a(e),label:e,title:`System name: ${e}`,value:t??""}))),i=n.controlsHolder();i.append(n.button({id:"config-delete",label:"Delete all values",danger:!0,onClick:async()=>{confirm("Are you sure you want to delete all configuration values?")&&await e.dropConfig().then((()=>{t.success({caption:"All values removed"}),Object.keys(o).forEach((e=>{const t=document.getElementById(a(e));t&&(t.value="",t.checked=!1)}))})).catch((()=>t.error({caption:"Failed to delete configuration values"})))}}),n.button({id:"config-save",label:"Save",onClick:async()=>{const n=Object.keys(o).reduce(((e,t)=>{const{value:n}=document.getElementById(a(t))??{};return e[t]=n,e}),{});await e.saveConfig(n).then((()=>t.success({caption:"Configuration updated"}))).catch((()=>t.error({caption:"Failed to save configuration values"})))}}));const s=n.container(),r=n.list();return r.append(...c),s.append(r,i),s.style.padding="2px",s}};export{o as ConfigTab};)=====";
#else
  const char* WEB_PAGE_MAIN = R"=====(<html>
  <head>
    <title>ST device</title>
    <script type="module" crossorigin src="/assets/minimal-script.js"></script>
  </head>
  <body>
    <ul id="tst"></ul>
    <h2>Device info</h2>
    <div id="info" class="grid">
      <label>Name</label>
      <div>
        <input id="name" type="text">
        <button id="sname">Save</button>
      </div>
    </div>
    <h2>WiFi settings</h2>
    <div class="grid">
      <label>SSID</label>
      <input id="ssid" type="text"/>
      <label>Password</label>
      <input id="password" type="text"/>
      <label>Mode</label>
      <select id="mode"></select>
    </div>
    <button id="swifi">Save</button>
    <h2>Danger</h2>
    <div>
      <button id="restart" style="background-color: red;">Restart device</button>
      <button id="factoryReset" style="background-color: red;">Factory reset</button>
    </div>
  </body>
  
  <style>
    body {
      display: flex;
      flex-direction: column;
      gap: 5px;
      align-items: center;
    }
    #tst {
      position: absolute;
      top: 5px;
      left: 5px;
    }
    .grid {
      display: grid;
      grid-template-columns: 1fr 2fr;
      row-gap: 2px;
      width: 354px;
    }
  </style>
</html>)=====";

  const char* SCRIPT_PAGE_MAIN = R"=====(const e="/wifi",t="/info/system",n="/danger",o="POST";let{hostname:s}=window.location;"localhost"===s&&(s="192.168.1.9");const i=e=>document.getElementById(e),a=(e,t,n)=>{const o=document.createElement(e);return t&&(o.innerHTML=t),n&&(o.value=n),o},d=e=>{i("tst").appendChild(a("li",e))},l=(e,t,n,o)=>{const i=new XMLHttpRequest;i.onloadend=()=>{o(i.response?JSON.parse(i.response):null,i.status)},i.open(e,`http://${s}${t}`,!0),i.setRequestHeader("Accept","application/json"),n&&i.setRequestHeader("Content-Type","application/json"),i.send(n?JSON.stringify(n):null)},r=()=>{l("PUT",t,{name:i("name").value},((e,t)=>{d(200===t?"Name updated":"Failed to update name: "+(null==e?void 0:e.error))}))},u=()=>{l(o,e,{ssid:i("ssid").value,password:i("password").value,mode:i("mode").value},((e,t)=>{d(200===t?"WiFi updated! Restart device to reconnect":"WiFi update failed: "+(null==e?void 0:e.error))}))},c=()=>{confirm("Are you sure you want to restart device right now?")&&l(o,n+"/restart",null,(()=>{d("Device should restart")}))},p=()=>{confirm("Are you sure you want to make FACTORY RESET?")&&confirm("Factory reset will wipe ALL settings. This can't be undone! Are you sure?")&&l(o,n+"/wipe",null,(()=>{d("Settings wiped"),d("Device should restart")}))};document.addEventListener("DOMContentLoaded",(()=>{i("sname").onclick=r,i("swifi").onclick=u,i("restart").onclick=c,i("factoryReset").onclick=p,l("GET",t,null,((e,t)=>{if(200!==t)return void d("Failed to load device info");i("name").value=e.name;const n=i("info");Object.entries(e).forEach((([e,t])=>{if("name"!==e){const o=a("input",null,t);o.disabled=!0,n.append(a("label",e),o)}}))})),l("GET",e,null,((e,t)=>{if(200!==t)return void d("Failed to load wifi info");const{settings:n,modes:o}=e,s=i("mode");Object.entries(o).forEach((([e,t])=>{s.appendChild(a("option",t,e))})),i("ssid").value=n.ssid,i("password").value=n.password,s.value=n.mode}))}));)=====";
#endif

#endif