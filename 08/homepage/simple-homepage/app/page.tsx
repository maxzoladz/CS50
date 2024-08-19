"use client";

import Link from "next/link";

export default function Page() {
  return (
    <>
      <main className="w-screen h-screen relative">
        <div className="flex justify-center items-center w-full h-full bg-cover bg-center">
          <div className="pl-20 md:pl-40 pb-56 md:pb-20 flex flex-col gap-5 z-[10] max-w-[750px]">
            <h1 className="text-[50px] text-white font-semibold">
              Maximilian Zoladz, currently studying
              <br></br>
              <a
                href="https://www.w-hs.de/wirtschaftsinformatik-ge/"
                target="_blank"
              >
                <span className="text-transparent bg-clip-text bg-gradient-to-r from-purple-500 to-cyan-500 font-bold">
                  business informatics
                </span>
              </a>
            </h1>
            <div className="flex-col md:flex-row hidden md:flex gap-5">
              <Link
                href="/contact-me"
                className="rounded-[20px] group relative bg-gradient-to-r from-purple-800 to-cyan-600 px-5 py-3 text-lg text-white max-w-[200px]"
              >
                <div className="absolute rounded-[20px] z-[1] bg-white inset-0 opacity-0 group-hover:opacity-20" />
                Contact Me
              </Link>

              <Link
                href="/holiday"
                className="rounded-[20px] group relative bg-gradient-to-r from-purple-800 to-cyan-600 px-5 py-3 text-lg text-white max-w-[200px]"
              >
                <div className="absolute rounded-[20px] z-[1] bg-white inset-0 opacity-0 group-hover:opacity-20" />
                My Projects
              </Link>

              <Link
                href="/about"
                className="rounded-[20px] group relative bg-gradient-to-r from-purple-800 to-cyan-600 px-5 py-3 text-lg text-white max-w-[200px]"
              >
                <div className="absolute rounded-[20px] z-[1] bg-white inset-0 opacity-0 group-hover:opacity-20" />
                Learn More
              </Link>
            </div>
          </div>
        </div>
      </main>
    </>
  );
}
