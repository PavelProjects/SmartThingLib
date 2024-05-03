#if ENABLE_WEB_PAGE 
const char* WEB_PAGE_MAIN = R"=====(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SmartThingDevice</title>
    <script type="module" crossorigin src="/assets/index.js"></script>
    <link rel="stylesheet" href="/assets/index.css">
  </head>
  <body>
    <h1 class="title">Control panel</h1>
    <div id="control-panel" class="bordered"></div>
    <div id="toasts-list" class="list"></div>
  </body>
</html>)=====";

const char* STYLE_PAGE_MAIN =
    R"=====(:root{--vt-c-black: #181818;--vt-c-black-soft: #222222;--vt-c-black-mute: #282828;--vt-c-indigo: #2c3e50;--vt-c-divider-dark-1: rgba(84, 84, 84, .65);--vt-c-divider-dark-2: rgba(84, 84, 84, .48);--vt-c-text-dark-1: var(--vt-c-white);--vt-c-text-dark-2: rgba(235, 235, 235, .64);--color-positive: hsla(160, 100%, 37%, 1);--color-accent: #2c3e50;--color-danger: rgba(147, 4, 4, .453);--vt-c-svg-fill: #666666;--background-tilt: #141313cd;--doc-height: 50px;--border-radius: 10px;--section-gap: 160px;--default-gap: 2px;--toast-width: 300px;--toast-min-height: 50px;--icon-size: 35px;--menu-item-width: 250px}:root{--color-background: var(--vt-c-black);--color-background-soft: var(--vt-c-black-soft);--color-background-mute: var(--vt-c-black-mute);--color-border: var(--vt-c-divider-dark-2);--color-border-hover: var(--vt-c-divider-dark-1);--color-heading: var(--vt-c-text-dark-1);--color-text: var(--vt-c-text-dark-2);--color-svg-fill: var() }*,*:before,*:after{box-sizing:border-box;margin:0;font-weight:400}body{min-height:100vh;color:var(--color-text);background:var(--color-background);transition:color .5s,background-color .5s;line-height:1.6;font-family:Inter,-apple-system,BlinkMacSystemFont,Segoe UI,Roboto,Oxygen,Ubuntu,Cantarell,Fira Sans,Droid Sans,Helvetica Neue,sans-serif;font-size:15px;text-rendering:optimizeLegibility;-webkit-font-smoothing:antialiased;-moz-osx-font-smoothing:grayscale}#control-panel{display:flex;flex-direction:row;column-gap:var(--default-gap);margin:0 auto;width:1000px}#toasts-list{position:absolute;bottom:5px;right:5px;z-index:999}.title{text-align:center;text-decoration:none;color:var(--color-positive)}.btn{background-color:#00bd7e33;border-color:transparent;border-radius:var(--border-radius);min-width:90px;min-height:40px;color:#000}.btn:hover{opacity:.5;cursor:pointer}input,select{min-height:40px;font-size:18px;background-color:var(--color-background);color:var(--color-text);outline:none;border:1px solid var(--color-border);border-radius:var(--border-radius)}.bordered{border:solid 2px var(--color-border);border-radius:var(--border-radius);padding:2px}.container{display:flex;flex-direction:column;gap:var(--default-gap);height:100%}.field-container{display:grid;grid-template-columns:1fr 1fr;border-radius:var(--border-radius)}input,select{background-color:var(--color-background);color:var(--color-text);outline:none;border:1px solid var(--color-border);border-radius:var(--border-radius)}.field-container .input-with-slot{display:flex;flex-direction:row;border:1px solid var(--color-border);border-radius:var(--border-radius)}.input-with-slot input{width:100%;border:none}.field-label{text-align:center}.list{display:flex;flex-direction:column;row-gap:var(--default-gap)}.required{background-color:#bd090033;color:#000}.menu-panel{display:flex;flex-direction:row;width:100%}.menu-items{width:var(--menu-item-width);height:fit-content;padding:2px}.menu-items h2{transition:.5s;cursor:pointer;border-radius:var(--border-radius);padding:5px;text-align:center;word-wrap:break-word}.menu-item-content{position:relative;width:calc(100% - var(--menu-item-width));margin-left:5px}.menu-selected{background-color:var(--vt-c-black-mute)}.update-button{position:absolute;top:0;right:0;display:none}.controls-holder{margin-top:auto;display:flex;flex-direction:row;gap:var(--default-gap)}.controls-holder button{width:100%}.hook-title{flex:1 1 auto;text-align:start}.hook-header{display:flex;flex-direction:row;gap:var(--default-gap);position:relative}.hooks-list-view{max-height:80vh;overflow-y:auto;margin-top:var(--default-gap)}.hook-view-controls{display:flex;flex-direction:row-reverse;column-gap:var(--default-gap);margin-bottom:5px}.toast{position:relative;border:1px solid var(--color-border);border-radius:var(--border-radius);width:var(--toast-width);min-height:var(--toast-min-height);padding:10px 5px 5px;z-index:1000;transition:.4s}.toast button{background-color:transparent;border-color:transparent;position:absolute;top:0;right:0;outline:none;-webkit-user-select:none;user-select:none}.toast h2,h3{text-align:center})=====";

const char* SCRIPT_PAGE_MAIN = R"=====(var M=Object.defineProperty;var $=(t,e,n)=>e in t?M(t,e,{enumerable:!0,configurable:!0,writable:!0,value:n}):t[e]=n;var T=(t,e,n)=>($(t,typeof e!="symbol"?e+"":e,n),n);(function(){const e=document.createElement("link").relList;if(e&&e.supports&&e.supports("modulepreload"))return;for(const o of document.querySelectorAll('link[rel="modulepreload"]'))s(o);new MutationObserver(o=>{for(const i of o)if(i.type==="childList")for(const r of i.addedNodes)r.tagName==="LINK"&&r.rel==="modulepreload"&&s(r)}).observe(document,{childList:!0,subtree:!0});function n(o){const i={};return o.integrity&&(i.integrity=o.integrity),o.referrerPolicy&&(i.referrerPolicy=o.referrerPolicy),o.crossOrigin==="use-credentials"?i.credentials="include":o.crossOrigin==="anonymous"?i.credentials="omit":i.credentials="same-origin",i}function s(o){if(o.ep)return;o.ep=!0;const i=n(o);fetch(o.href,i)}})();const a={title:(t,e="h1")=>{const n=document.createElement(e);return n.classList.add("title"),n.innerHTML=t,n},container:(t={bordered:!1})=>{const e=document.createElement("div");return e.classList.add("container"),t.bordered&&e.classList.add("bordered"),e},list:()=>{const t=document.createElement("div");return t.classList.add("list"),t},button:({id:t,label:e,labelElement:n="h2",onClick:s,danger:o=!1,visible:i=!0})=>{const r=document.createElement("button");t&&(r.id=t),r.classList.add("btn");const c=`<${n}>${e}</${n}>`;return r.innerHTML=c,s&&(r.onclick=async()=>{r.disabled=!0,r.innerHTML="Loading...";try{await s()}catch(d){console.error(d)}finally{r.innerHTML=c,r.disabled=!1}}),o&&(r.style.backgroundColor="var(--color-danger)"),i||(r.style.display="none"),r},icon:({id:t,icon:e,onClick:n=()=>{},visible:s=!0})=>{const o=document.createElement("span");return t&&(o.id=t),o.ariaHidden=!0,o.role="img",o.innerHTML=e,s||(o.style.display="none"),o.style.cursor="pointer",o.onclick=n,o},input:({id:t,label:e,value:n,disabled:s=!1,type:o="text",slot:i,props:r={}})=>{const c=document.createElement("div");c.classList.add("field-container");const d=document.createElement("h2");d.classList.add("field-label"),d.innerHTML=e;const m=document.createElement("div");m.classList.add("input-with-slot");const p=document.createElement("input");return t&&(p.id=t),p.disabled=s,p.value=n,p.type=o,Object.entries(r).forEach(([g,w])=>p.setAttribute(g,w)),m.appendChild(p),i&&m.appendChild(i),c.append(d,m),c},combobox:({id:t,value:e,values:n,label:s,disabled:o=!1,onChange:i,props:r={}})=>{const c=document.createElement("div");if(c.classList.add("field-container"),s){const m=document.createElement("h2");m.classList.add("field-label"),m.innerHTML=s,c.appendChild(m)}const d=document.createElement("select");return t&&(d.id=t),d.disabled=o,d.appendChild(document.createElement("option")),i&&(d.onchange=()=>i(d.value)),Object.entries(r).forEach(([m,p])=>d.setAttribute(m,p)),c.append(d),I(c,n),e&&(d.value=e),c},tree:t=>{const e=document.createElement("ul");return Object.entries(t).forEach(([n,s])=>e.appendChild(S({key:n,value:s}))),e},controlsHolder:()=>{const t=document.createElement("div");return t.classList.add("controls-holder"),t}},b={pencil:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M20.71,7.04C21.1,6.65 21.1,6 20.71,5.63L18.37,3.29C18,2.9 17.35,2.9 16.96,3.29L15.12,5.12L18.87,8.87M3,17.25V21H6.75L17.81,9.93L14.06,6.18L3,17.25Z"></path></svg>',trash:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M19,4H15.5L14.5,3H9.5L8.5,4H5V6H19M6,19A2,2 0 0,0 8,21H16A2,2 0 0,0 18,19V7H6V19Z"></path></svg>',cross:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M13.46,12L19,17.54V19H17.54L12,13.46L6.46,19H5V17.54L10.54,12L5,6.46V5H6.46L12,10.54L17.54,5H19V6.46L13.46,12Z"></path></svg>',save:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M15,9H5V5H15M12,19A3,3 0 0,1 9,16A3,3 0 0,1 12,13A3,3 0 0,1 15,16A3,3 0 0,1 12,19M17,3H5C3.89,3 3,3.9 3,5V19A2,2 0 0,0 5,21H19A2,2 0 0,0 21,19V7L17,3Z"></path></svg>',update:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M17.65,6.35C16.2,4.9 14.21,4 12,4A8,8 0 0,0 4,12A8,8 0 0,0 12,20C15.73,20 18.84,17.45 19.73,14H17.65C16.83,16.33 14.61,18 12,18A6,6 0 0,1 6,12A6,6 0 0,1 12,6C13.66,6 15.14,6.69 16.22,7.78L13,11H20V4L17.65,6.35Z"></path></svg>'};function I(t,e){if(!e)return;const n=t.getElementsByTagName("select")[0];if(!n){console.error("Can't find select in combobox");return}let s;Array.isArray(e)?s=e.map(o=>({key:o,caption:o})):s=Object.entries(e).map(([o,i])=>({key:o,caption:i})),s.forEach(({key:o,caption:i})=>{const r=document.createElement("option");r.value=o,r.innerHTML=i,n.appendChild(r)})}const S=({key:t,value:e})=>{const n=document.createElement("li");return n.append(t+": ",D(e)),n},D=t=>{if(Array.isArray(t)){const e=document.createElement("ul");return t.forEach(n=>{const s=document.createElement("li");s.innerHTML=n,e.appendChild(s)}),e}else if(t instanceof Object){const e=document.createElement("ul");return Object.entries(t).forEach(([n,s])=>{const o=document.createElement("li");o.appendChild(S({key:n,value:s})),e.appendChild(o)}),e}else{const e=document.createElement("span");return e.innerHTML=t,e}};class k{constructor(e,n){T(this,"selected",{});this.id=e,this.menuItems=n}create(){const e=document.createElement("div");e.classList.add("menu-panel"),this.viewDiv=document.createElement("div"),this.viewDiv.classList.add("menu-items","list","bordered"),this.viewDiv.id=this.id,Object.entries(this.menuItems).forEach(([s,{name:o}])=>{const i=document.createElement("h2");i.id=s,i.innerHTML=o,i.onclick=()=>this.open(s),this.viewDiv.appendChild(i)}),this.contentDiv=document.createElement("div"),this.contentDiv.classList.add("menu-item-content"),this.contentDiv.id=this.id+"-content",this.loadingTitle=a.title("Loading...","h2"),this.loadingTitle.style.display="none",this.contentDiv.appendChild(this.loadingTitle);const n=a.icon({id:this.id+"-update",icon:b.update,onClick:()=>this.updateContent()});return n.classList.add("update-button"),this.contentDiv.appendChild(n),e.append(this.viewDiv,this.contentDiv),e}open(e){const n=document.getElementById(e);if(!n){console.error("Failed to open menuItem id="+e+": element not found");return}this.selected.item&&(this.selected.item.classList.remove("menu-selected"),this.selected.content.style.display="none");let s=document.getElementById(e+"-content");s?s.style.display="":(s=this.createContent(e),this.contentDiv.appendChild(s)),n.classList.add("menu-selected"),this.selected.name=e,this.selected.item=n,this.selected.content=s,document.getElementById(this.id+"-update").style.display="unset"}updateContent(){this.selected&&(this.selected.content.remove(),this.selected.content=this.createContent(this.selected.name),this.contentDiv.appendChild(this.selected.content))}createContent(e){const n=e+"-content",s=a.container();return s.id=n,this.menuItems[e].title&&s.appendChild(a.title(this.menuItems[e].title)),this.loadContent(s,e),s}async loadContent(e,n){try{this.loading(!0),e.appendChild(await this.menuItems[n].content())}catch(s){console.error(s)}finally{this.loading(!1)}}loading(e){this.loadingTitle.style.display=e?"":"none"}}let{hostname:C}=window.location;C==="localhost"&&(C="192.168.2.2");const f="Something gone wrong",h={info:async()=>{try{const{data:t}=await u({path:"/info/system"});return t??{}}catch(t){console.error(t)}},actions:async()=>{try{const{data:t}=await u({path:"/info/actions"});return t??{}}catch(t){console.error(t)}},configInfo:async()=>{try{const{data:t}=await u({path:"/info/config"});return t??{}}catch(t){console.error(t)}},getWifi:async()=>{try{const{data:t}=await u({path:"/wifi"});return t}catch(t){console.error(t)}},saveWifi:async t=>{try{const{status:e}=await u({path:"/wifi",method:"POST",payload:t});return e===200}catch(e){console.error(e)}},saveName:async t=>{try{const{status:e}=await u({path:"/info/system",method:"PUT",payload:{name:t}});return e===200}catch(e){console.error(e)}},execAction:async t=>{try{const{status:e}=await u({method:"PUT",path:"/actions",params:{action:t}});return e===200}catch(e){console.error(e)}},sensors:async()=>{try{const{data:t}=await u({path:"/sensors"});return t??{}}catch(t){console.error(t)}},states:async()=>{try{const{data:t}=await u({path:"/states"});return t??{}}catch(t){console.error(t)}},config:async()=>{try{const{data:t}=await u({path:"/config"});return t??{}}catch(t){console.error(t)}},dropConfig:async()=>{try{const{status:t}=await u({method:"DELETE",path:"/config/delete/all"});return t===200}catch(t){console.error(t)}},saveConfig:async t=>{try{const{status:e}=await u({method:"POST",path:"/config",payload:t});return e===200}catch(e){console.error(e)}},hooks:async({observable:{name:t,type:e}})=>{try{const{data:n}=await u({path:"/hooks/by/observable",params:{name:t,type:e}});return n||[]}catch(n){console.error(n)}},hooksTemplates:async t=>{try{const{data:e}=await u({path:"/hooks/templates",params:{type:t}});return e||[]}catch(e){console.error(e)}},createHook:async({observable:{name:t,type:e},hook:n})=>{try{const{status:s}=await u({path:"/hooks",method:"POST",payload:{observable:{name:t,type:e},hook:n}});return s===201}catch(s){console.error(s)}},updateHook:async({observable:{name:t,type:e},hook:n})=>{try{const{status:s}=await u({path:"/hooks",method:"PUT",payload:{observable:{name:t,type:e},hook:n}});return s===200}catch(s){console.error(s)}},deleteHook:async({observable:{name:t,type:e},id:n})=>{try{const{status:s}=await u({path:"/hooks",method:"DELETE",params:{name:t,type:e,id:n}});return s===200}catch(s){console.error(s)}},metrics:async()=>{try{const{data:t}=await u({path:"/metrics"});return t??{}}catch(t){console.error(t)}}};function B(t){if(!t||!Object.keys(t))return"";const e=Object.entries(t).map(([n,s])=>`${n}=${s}`);return e.length>0?"?"+e.join("&"):""}function u({method:t="GET",path:e,payload:n,params:s}){let o=new XMLHttpRequest;o.open(t,`http://${C}${e[0]!="/"?"/":""}${e}${B(s)}`),o.setRequestHeader("Accept","application/json"),n&&o.setRequestHeader("Content-Type","application/json");let i;const r=new Promise(c=>i=c);return o.onreadystatechange=()=>{o.readyState===4&&i({data:o.response?JSON.parse(o.response):null,status:o.status})},o.send(n?JSON.stringify(n):null),r}let j=0;const N=5e3,v={INFO:"info",SUCCESS:"success",WARNING:"warning",ERROR:"error"};function _(t){const e=document.getElementById(t);e&&e.remove()}function x(t){switch(t){case v.ERROR:return"rgb(171, 12, 12)";case v.SUCCESS:return"rgb(2, 147, 74)";case v.WARNING:return"rgb(147, 106, 2)";default:return"rgb(0, 112, 122)"}}function y({type:t=v.INFO,caption:e,description:n=""}){const s=document.createElement("div");s.classList.add("toast");const o="toast-"+j++;s.id=o,s.style.backgroundColor=x(t);const i=document.createElement("h2");i.id=o+"-caption",i.innerHTML=e;const r=document.createElement("div");r.id=o+"-description",r.style.overflowWrap="break-word",r.innerHTML=n;const c=document.createElement("button");c.id=o+"-close",c.innerHTML="X",c.onclick=()=>_(o),s.append(i,r,c),document.getElementById("toasts-list").appendChild(s),setTimeout(()=>_(o),N)}const l={info:({caption:t,description:e})=>y({caption:t,description:e}),error:({caption:t,description:e})=>y({type:v.ERROR,caption:t,description:e}),success:({caption:t,description:e})=>y({type:v.SUCCESS,caption:t,description:e}),warning:({caption:t,description:e})=>y({type:v.WARNING,caption:t,description:e})},R={name:"Information",title:"Device information",content:async()=>{const t=await h.info();if(!t){l.error({caption:f,description:"Failed to fetch system information"});return}document.title=`SmartThing ${t.name}(${t.type})`;const e=a.list();return e.append(a.input({id:"device-name",label:"Device name",value:t.name||"",slot:a.button({id:"save-device-name",label:"save",onClick:async()=>{const n=document.getElementById("device-name"),s=n.value;if(!s||s.length===0){n.classList.add("required"),l.error({caption:"Device name can't be empty!"});return}const o=await h.saveName(s);n.classList.remove("required"),o?l.success({caption:"Name updated",description:"New device name: "+s}):l.error({caption:"Name update failed",description:"Failed to update device name"})}})}),a.input({label:"Device type",value:t.type,disabled:!0}),a.input({label:"Firmware version",value:t.version,disabled:!0,type:"number"}),a.input({label:"Chip model",value:t.chip_model,disabled:!0}),a.input({label:"Chip revision",value:t.chip_revision,disabled:!0})),e}},V={name:"WiFi",title:"WiFi settings",content:async()=>{const{settings:t,modes:e}=await h.getWifi();if(!t){l.error({caption:f,description:"Failed to fetch WiFi settings"});return}const n=a.list();n.append(a.input({id:"ssid",label:"SSID",value:t.ss||""}),a.input({id:"password",label:"password",value:t.ps||""}),a.combobox({id:"mode",label:"mode",values:e,value:t.md}));const s=a.controlsHolder();s.appendChild(a.button({label:"Save and reconnect",onClick:async()=>{await h.saveWifi({ssid:document.getElementById("ssid").value||"",password:document.getElementById("password").value||"",mode:document.getElementById("mode").value||""})?l.success({caption:"WiFi settings updated"}):l.error({caption:"Failed to update WiFi settings",description:"Check device logs for additional information"})}}));const o=a.container();return o.append(n,s),o}},W={name:"Actions",title:"Actions list",content:async()=>{const t=await h.actions();if(!t){l.error({caption:f,description:"Failed to fetch device actions"});return}const e=a.list();return Object.entries(t).forEach(([n,s])=>{e.appendChild(a.button({id:"action_"+n,label:s,labelElement:"h1",onClick:async()=>{await h.execAction(n)?l.success({caption:"Done",description:`Action "${s}" performed successfully`}):l.error({caption:"Action failed",description:`Failed to perform action "${s}"`})}}))}),e}};function L(t){return typeof t!="string"||t.length==0?"":t.split("").reduce((e,n)=>(n==="_"?e+=" ":n===n.toUpperCase()?e+=" "+n.toLowerCase():e+=n,e),"")}const P=["id","type","readonly"];function q(t){return P.includes(t)}class A{constructor({id:e="",hook:n,template:s,observable:o,parent:i}){this.id=e,this.hook=n,this.template=s,this.observable=o,this.parent=i,this.fields=Object.entries(this.hook).filter(([r,c])=>!q(r)).reverse(),this.controls={delete:a.icon({icon:b.trash,onClick:()=>this.delete()}),edit:a.icon({icon:b.pencil,onClick:()=>this.edit()}),cancel:a.icon({icon:b.cross,onClick:()=>this.cancel(),visible:!1}),save:a.icon({icon:b.save,onClick:()=>this.save(),visible:!1})}}create(){const e=document.getElementById(this.id);if(this.id&&e)return e;const n=a.container({bordered:!0});n.id=this.id;const s=document.createElement("div");s.classList.add("hook-header");const{id:o,caption:i,type:r}=this.hook,c=a.title(`[${o}] ${i||L(r)}`,"h2");c.classList.add("hook-title");const d=document.createElement("div");d.classList.add("hook-view-controls"),Object.values(this.controls).forEach(p=>d.appendChild(p)),s.append(c,d);const m=a.list();return this.fields.forEach(([p,g])=>{const{required:w}=this.template[p]||!1,H={id:`cb_${o}_${p}`,label:L(p),value:g,disabled:!0,props:{required:w}};let E;this.template[p]&&this.template[p].values?E=a.combobox({...H,values:this.template[p].values}):E=a.input(H),m.appendChild(E)}),n.append(s,m),n}edit(e=!0){this.fields.forEach(([n,s])=>{document.getElementById(`cb_${this.hook.id}_${n}`).disabled=!e}),e?(this.controls.cancel.style.display="",this.controls.save.style.display="",this.controls.delete.style.display="none",this.controls.edit.style.display="none"):(this.controls.cancel.style.display="none",this.controls.save.style.display="none",this.controls.delete.style.display="",this.controls.edit.style.display="")}validate(){let e=!0;return this.fields.forEach(([n,s])=>{const o=document.getElementById(`cb_${this.hook.id}_${n}`);o.getAttribute("required")=="true"&&!o.value&&(e=!1,o.classList.add("required"))}),e}async save(){if(!this.validate())return;this.fields.forEach(([n,s])=>{this.hook[n]=document.getElementById(`cb_${this.hook.id}_${n}`).value});let e;this.hook.id==="New"?(delete this.hook.id,e=await h.createHook({observable:this.observable,hook:this.hook})):e=await h.updateHook({observable:this.observable,hook:this.hook}),e?(l.success({caption:`Hook ${this.hook.id==="New"?"created":"updated"}!`}),document.getElementById(this.id).remove(),this.parent.update()):l.error({caption:"Failed to save toast",description:"Check device logs for additional information"})}async delete(){confirm("Are you sure you wan to delete hook "+this.hook.id+"?")&&(await h.deleteHook({observable:this.observable,id:this.hook.id})?(l.success({caption:"Hook deleted"}),this.parent.update()):l.error({caption:"Failed to delete hook",description:"Check device logs for additional information"}))}cancel(){this.hook.id==="New"?(document.getElementById(this.id).remove(),this.parent.update()):this.edit(!1)}}class F{constructor({id:e="",observable:n}){this.id=e,this.observable=n}create(){const e=document.getElementById(this.id);if(this.id&&e)return e;const n=document.createElement("div");return n.id=this.id,this.comboboxTemplates=a.combobox({values:[],label:"Add hook of type",onChange:s=>{this.addNewHook(s)}}),this.list=a.list(),this.list.id="cb_list_"+this.id,this.list.classList.add("hooks-list-view"),n.append(this.comboboxTemplates,this.list),this.firstLoad(),n}update(){this.loadHooks()}async firstLoad(){await this.loadTemplates(),this.loadHooks()}async loadTemplates(){if(this.templates=await h.hooksTemplates(this.observable.type),!this.templates){l.error({caption:"Something gone wrong",description:"Failed to fetch hooks templates"});return}I(this.comboboxTemplates,Object.keys(this.templates).filter(e=>e!=="default").reduce((e,n)=>(e[n]=L(n),e),{}))}async loadHooks(){if(this.templates){if(this.list.innerHTML="",this.hooks=void 0,this.hooks=await h.hooks({observable:this.observable}),!this.hooks){l.error({caption:"Something gone wrong",description:`Failed to fetch hooks for [${this.observable.type}]${this.observable.name}`});return}if(!this.hooks||this.hooks.length===0){this.list.appendChild(a.title("No hooks added yet","h3"));return}this.hooks.forEach(e=>this.list.appendChild(new A({id:"cb_"+e.id,hook:e,template:{...this.templates[e.type],...this.templates.default},observable:this.observable,parent:this}).create()))}}addNewHook(e){const n=document.getElementById("cb_new");if(n&&n.remove(),!e)return;const s={...this.templates[e],...this.templates.default},o=Object.entries(s).reduce((r,[c,d])=>(r[c]=d.default||"",r),{id:"New",type:e}),i=new A({id:"cb_new",hook:o,template:s,observable:this.observable,parent:this});this.list.prepend(i.create()),i.edit()}}const U={name:"Sensors",title:"Sensors values",content:async()=>{const t=await h.sensors();if(!t){l.error({caption:f,description:"Failed to fetch sensors"});return}if(Object.keys(t).length===0)return a.title("No sensors configured","h2");const e=Object.entries(t).reduce((s,[o,{value:i,type:r}])=>(s["sensors-menu-"+o]={name:`${o} (${r}): ${i}`,title:"Hooks",content:async()=>new F({id:"cb_view_"+o,observable:{type:"sensor",name:o}}).create()},s),{});return new k("sensors-menu",e).create()}},Z={name:"States",title:"Device states values",content:async()=>{const t=await h.states();if(!t){l.error({caption:f,description:"Failed to fetch device states"});return}if(Object.keys(t).length===0)return a.title("No states configured","h2");const e=Object.entries(t).reduce((s,[o,i])=>(s["state-menu-"+o]={name:`${o}: ${i}`,title:"Hooks",content:async()=>new F({id:"cb_view_"+o,observable:{type:"state",name:o}}).create()},s),{});return new k("states-menu",e).create()}},G={name:"Configuration",title:"Configuration values",content:async()=>{const t=await h.configInfo();if(!t){l.error({caption:f,description:"Failed to fetch configuration information"});return}if(Object.keys(t).length===0)return a.title("No config entries","h2");const e=await h.config();if(!e){l.error({caption:f,description:"Failed to fetch configuration values"});return}const n=a.list();Object.entries(t).forEach(([i,{caption:r,type:c}])=>{n.appendChild(a.input({id:i,label:r,type:c,value:e[i]||""}))});const s=a.controlsHolder();s.append(a.button({id:"config-delete",label:"Delete all values",danger:!0,onClick:async()=>{confirm("Are you sure you want to delete all configuration values?")&&(await h.dropConfig()?l.success({caption:"All values removed"}):l.error({caption:"Failed to delete configuration values"}))}}),a.button({id:"config-save",label:"Save",onClick:async()=>{const i={};Object.keys(t).forEach(c=>i[c]=document.getElementById(c).value),await h.saveConfig(i)?l.success({caption:"Configuration updated"}):l.error({caption:"Failed to save configuration values"})}}));const o=a.container();return o.append(n,s),o}},J={name:"Metrics",title:"Device metrics",content:async()=>{const t=await h.metrics();if(!t){l.error({caption:f,description:"Failed to fetch device metrics"});return}return a.tree(t)}},O=new k("menu-main",{info:R,wifi:V,actions:W,sensors:U,states:Z,configuration:G,metrics:J});window.onload=()=>{document.getElementById("control-panel").appendChild(O.create()),O.open("info")};)=====";
#endif