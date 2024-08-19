import type { Metadata } from "next";
import { Inter } from "next/font/google";
import "./globals.css";
import * as React from "react";
import { NextUIProvider } from "@nextui-org/react";

const inter = Inter({ subsets: ["latin"] });

export const metadata: Metadata = {
  title: "Maximilian Zoladz",
  description: "This is my portfolio!",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en" id="penis" suppressHydrationWarning>
      <body className="bg-black">
        <NextUIProvider>
          <div className="dark">{children}</div>
        </NextUIProvider>
      </body>
    </html>
  );
}
